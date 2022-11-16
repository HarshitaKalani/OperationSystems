#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int state[5];
int philosopher[5]={0,1,2,3,4};
#define THINKING 2
#define HUNGRY 1
#define EATING 0
sem_t S[5];
sem_t mutex;
void conditions(int i){
    if(state[i]==HUNGRY && state[(1+i)%5]!=EATING && state[(4+i)%5]!=EATING){
        state[i]=3;
        sleep(2);
        // cout<<"Philosopher "<<i+1<<"takes fork"<<(4+i)%5+1<<"and fork"<<i+1<<endl;
        // cout<<"Philosopher "<<i+1<<" is eating"<<endl;
        printf("Philosopher %d takes fork %d and %d\n",
			   1+i, (4+i)%5 + 1, 1+i);

		printf("Philosopher %d is Eating\n", 1+i);
        sem_post(&S[i]);
    }
}

void pickFork(int i){
    sem_wait(&mutex);
    state[i]=HUNGRY;
    // cout<<"Philosopher "<<i+1<<" is hungry"<<endl;
    printf("Philosopher %d is Hungry\n", 1+i);
    conditions(i);
    sem_post(&mutex);
    sem_wait(&S[i]);
    sleep(1);
}
void putdownFork(int i){
    sem_wait(&mutex);
    state[i]=THINKING;
    // cout<<"Philosopher "<<i+1<<" puts fork"<<(4+i)%5+1<<"and fork"<<i+1<<"down"<<endl;
    // cout<<"Philosopher "<<i+1<<" is thinking"<<endl;
    printf("Philosopher %d putting fork %d and %d down\n",1+i, (4+i)%5+1, 1+i);
	printf("Philosopher %d is thinking\n", 1+i);
    conditions((4+i)%5);
    conditions((1+i)%5);
    sem_post(&mutex);
}
void * philos(void *num){
    while(1){
        int *i = (int *)num;
        sleep(1);
        if(state[*i]==THINKING && state[((*i)+4)%5] == EATING && state[((*i)+1)%5] == EATING) {
			printf("Deadlock situation detected!");
            printf("Philosopher  %d  putting fork %d and %d down", *i+1, ((*i)+4)%5+1,((*i)+1)%5);
        }
        pickFork(*i);
        sleep(0);
        putdownFork(*i);
    }
}
int main(){
    int i;
    pthread_t thread_id[5];
    sem_init(&mutex,0,1);
    for(i=0;i<5;i++)
        sem_init(&S[i],0,0);
    for(i=0;i<5;i++){
        pthread_create(&thread_id[i],NULL,philos,&philosopher[i]);
        // cout<<"Philosopher "<<i+1<<" is thinking"<<endl;
        printf("Philosopher %d is thinking\n", 1+i);
    }
    for(i=0;i<5;i++)
        pthread_join(thread_id[i],NULL);
    return 0;
}