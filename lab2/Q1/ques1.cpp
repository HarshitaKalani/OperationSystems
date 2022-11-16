#include <bits/stdc++.h>
using namespace std;
#include<fcntl.h>

int main(int argc, char* argv[]){
    if(argc!=3){
        fprintf(stderr, "Incorrect number of arguments");
        exit(1);
    }
   
    char c;
    int file_1 = open(argv[1], O_RDONLY);
    int file_2 = open(argv[2], O_WRONLY);
    if(file_1<0 or file_2<0) 
    {
        // fprintf(stderr, "%d, %d", file_1, file_2);
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }

    while(read(file_1, &c, 1)){
        if(c>96 and c<123){
            c=c-32;
        }
        else if(c>64 and c<91){
            c=c+32;
        }
        write(file_2, &c, 1);
    }
    fprintf(stdout, "case converted");
    exit(0);
    
    
}