#include<bits/stdc++.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h> 
#include <errno.h> 
#include <unistd.h> 

using namespace std;
#define MAX_INPUT_SIZE 1024
int prec(char op){
    if(op=='+' or op=='-') return 1;
    if(op=='*' or op=='/') return 2;
    if(op=='^') return 3;
    return 0;
}
int apply(int valx, int valy, char op){
    if(op=='+') return valx+valy;
    if(op=='-') return valx-valy;
    if(op=='*') return valx*valy;
    if(op=='/') return valx/valy;
    if(op=='^') return pow(valx, valy);
    return 0;
}

void eval(stack<int>&values, stack<char>&operators){
    int valy=values.top();
    values.pop();
    int valx=values.top();
    values.pop();
    char op= operators.top();
    operators.pop();
    values.push(apply(valx, valy, op));
}
int evaluate(string s){
    stack<int>values;
    stack<char> operators;
    for(int i=0;i<s.length();i++){
        if(s[i]==' ') continue;
        else if(isdigit(s[i])){
            int val=0;
            while(i<s.length() && isdigit(s[i])){
                val=(val*10)+(s[i]-'0');
                i++;
            }
            values.push(val);
            i--;
        }
        else if(s[i]=='('){
            operators.push(s[i]);
        }
        else if(s[i]==')'){
            while(!operators.empty() && operators.top()!='('){
                eval(values, operators);
            }
            if(!operators.empty()) operators.pop();
        }
        else{
            while(!operators.empty() && prec(operators.top())>=prec(s[i])){
                eval(values, operators);
            }
            operators.push(s[i]);
        }
    }
    while(!operators.empty()){
        eval(values, operators);
    }
    return values.top();

}
int main(int argc, char* argv[]){
    int portnum, sockfd, n=1;
    char inputbuf[MAX_INPUT_SIZE];
    struct sockaddr_in server_addr;
    fd_set readfds;
    int maxclients=30;
    int clsock[30]={0};
    sockfd= socket(AF_INET, SOCK_STREAM, 0);
    portnum= atoi(argv[1]);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(portnum);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    if(sockfd<0){
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&n, sizeof(n))<0){
        perror("Setsockpot error");
        exit(EXIT_FAILURE);
    }
    if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
    if(listen(sockfd, 10)<0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    int len=sizeof(server_addr);
    cout<<"Waiting for the client to connect"<<'\n';
    int max_sd, sd, socknew, valread;
    do{
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        max_sd=sockfd;
        for(int i=0;i<maxclients;i++){
            sd=clsock[i];
            if(sd>0) FD_SET(sd, &readfds);
            max_sd=max(max_sd, sd);
        }
        int activity= select(max_sd+1, &readfds, NULL, NULL, NULL);
        if((activity<0) && errno!=EINTR) cout<<"Select error"<<'\n';
        if(FD_ISSET(sockfd, &readfds)){
            if((socknew=accept(sockfd, (struct sockaddr *)&server_addr, (socklen_t*)&len))<0){
            perror("accept");
            exit(EXIT_FAILURE);
            }
            cout<<"New connection, connected with client socket number "<<socknew<<", IP: "<<inet_ntoa(server_addr.sin_addr)<<", port: "<<ntohs(server_addr.sin_port)<<'\n';
            for(int i=0;i<maxclients;i++){
            //if position is empty
            if(clsock[i]==0){
                clsock[i]=socknew;
                cout<<"Adding to list of sockets as "<<i<<'\n';
                break;
            }
        }
    }
    for(int i=0;i<maxclients;i++){
        sd= clsock[i];
        if(FD_ISSET(sd, &readfds)){
            if(valread= read(sd, inputbuf, MAX_INPUT_SIZE)==0){
                getpeername(sd, (struct sockaddr*)&server_addr, (socklen_t*)&len);
                cout<<"Host disconnected, IP"<<inet_ntoa(server_addr.sin_addr)<<", port "<<ntohs(server_addr.sin_port)<<'\n';
                close(sd);
                clsock[i]=0;
            }
            else{
                string exp(inputbuf);
                cout<<"Client socket sent message: "<<inputbuf<<'\n';
                int answer=evaluate(inputbuf);
                cout<<"Sending reply: "<<answer<<'\n';
                char result[1024];
                sprintf(result,"%d",answer);
                send(sd,&result, sizeof(result),0);
                }
            }
        }
    }
    while(1);

    return 0;
}
