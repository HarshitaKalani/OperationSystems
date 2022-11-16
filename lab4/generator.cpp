#include<bits/stdc++.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;

int main(int argc, char* argv[]){
    int portnum;
    if(argc<2) {
        fprintf(stderr,"usage %s <server-ip-addr> <server-port>\n", argv[0]);
        exit(0);
    }
    portnum = atoi(argv[2]);
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        string s=argv[i];
        std::filesystem::copy("client.cpp",s+".cpp");
    }
   
}