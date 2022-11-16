#include<bits/stdc++.h>
#include<fcntl.h>
using namespace std;
int main(int argc, char *argv[]){
    int count=0;
    char c;
    if(argc!=2){
        fprintf(stderr, "Incorrect number of arguments");
        exit(1);
    }
    int file1=open(argv[1], O_RDONLY);
    if(file1<0){
        fprintf(stderr, "Error while opening file");
        exit(1);
    }
    else{
        while(read(file1, &c, 1)){
            if(isdigit(c)){
                count++;
            }
        }
        fprintf(stdout, "Non alphabetic chars: %d " , count);
    }
}