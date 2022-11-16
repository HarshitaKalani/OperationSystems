#include<bits/stdc++.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;

void call(){
    system("g++ consumer.cpp -o consumer");
    system("./consumer");
}
int main(){
    const int size=4096;
    const char* name= "Producer_consumer";
    int shmfd = shm_open(name,O_CREAT|O_RDWR,0666);
    void* ptr =mmap(0,size,PROT_WRITE,MAP_SHARED,shmfd,0);
    ftruncate(shmfd,size);
    for(int i=0;i<10;i++){
        srand(time(0));
        ptr=mmap(0,size,PROT_WRITE,MAP_SHARED,shmfd,0);
        int x;
        cout<<"Enter number to be produced: "; cin>>x;
        sprintf((char*)ptr,"%d",x);
        ptr=ptr+sizeof(x);
        cout<<"Message produced by producer: "<<x<<'\n';
        call();
    }
    shm_unlink(name);
    return 0;      
}