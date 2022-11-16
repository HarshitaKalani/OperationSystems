#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;
#define MAX_INPUT_SIZE 1024

int main(int argc, char* argv[]){
    int sockfd, portnum, n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    char inputbuf[MAX_INPUT_SIZE];
    if(argc<3) {
        fprintf(stderr,"usage %s <server-ip-addr> <server-port>\n", argv[0]);
        exit(0);
    }
    portnum = atoi(argv[2]);
    
    if (sockfd < 0)
    {
        fprintf(stderr, "ERROR opening socket\n");
        exit(1);
    }
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnum);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    if (connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) <0)
        {
        fprintf(stderr, "ERROR connecting\n");
        exit(1);
    }
    cout<<"Connected to server\n";
    do{
        bzero(inputbuf,MAX_INPUT_SIZE);
        cout<<"Please enter the message to the server: ";
        cin>>inputbuf;
        send(sockfd,&inputbuf,sizeof(inputbuf),0);
        bzero(inputbuf,MAX_INPUT_SIZE);
        recv(sockfd,inputbuf,sizeof(inputbuf),0); 
        cout<<"Server replied: "<<inputbuf<<'\n';

        } 
    while(1);
    return 0;
    
}