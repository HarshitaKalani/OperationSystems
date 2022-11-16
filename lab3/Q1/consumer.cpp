#include<bits/stdc++.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;

int main(){
    const int size=4096;
    const char *name= "Producer_consumer";
    int shmfd = shm_open(name, O_RDONLY, 0666);
    void *ptr=mmap(0, size, PROT_READ, MAP_SHARED, shmfd, 0);
    int x;
    int y= atoi((char*)ptr);
    cout<<"Enter 1 to consume: "; cin>>x;

    if(x==1){
        cout<<"Message received by consumer: "<<y<<'\n';
    }
    else{
        while(x!=1){
            cout<<"Invalid entry, Enter 1 to consume: "; cin>>x;
        }
        cout<<"Message received by consumer: "<<y<<'\n';
    }
    return 0;
}