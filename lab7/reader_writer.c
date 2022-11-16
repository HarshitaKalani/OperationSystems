#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include<semaphore.h>
sem_t wrt;
pthread_mutex_t mutex;

int count=1;
int noreader=0;
void *reader(void *arg){
    pthread_mutex_lock(&mutex);
    noreader++;
    if(noreader==1){
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    printf("Reader %d: read count as %d\n",*((int *)arg),count);
    pthread_mutex_lock(&mutex);
    noreader--;
    if(noreader==0){
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

void *wrtr(void *arg){
    sem_wait(&wrt);
    count++;
    printf("Writer %d: incremented count to %d\n", (*((int *)arg)), count);
    sem_post(&wrt);
    return 0;
}

int main(){
    pthread_t r[5],w[5];
    pthread_mutex_init(&mutex,NULL);
    sem_init(&wrt,0,1);
    int a[5]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        pthread_create(&r[i],NULL,reader,(void *)&a[i]);
    }
    for(int i=0;i<5;i++){
        pthread_create(&w[i],NULL,wrtr,(void *)&a[i]);
    }
    for(int i=0;i<5;i++){
        pthread_join(r[i],NULL);
    }
    for(int i=0;i<5;i++){
        pthread_join(w[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}