#include<bits/stdc++.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
    int portnum, sockfd, n;
    sockfd= socket(AF_INET, SOCK_STREAM, 0);
    char inputbuf[MAX_INPUT_SIZE];
    portnum= atoi(argv[1]);
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(portnum);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(sockfd, 1);
    cout<<"Waiting for client to connect"<<'\n';
    int clientfd=accept(sockfd,NULL,NULL);
    cout<<"New connection"<<", ip is "<<inet_ntoa(server_addr.sin_addr)<<" and port is "<<ntohs(server_addr.sin_port)<<'\n';
    
    close(sockfd);
    
    int pid = fork();
    if(pid==0){
        do{
            // bzero(inputbuf,MAX_INPUT_SIZE);
            // n=read(clientfd,inputbuf,(MAX_INPUT_SIZE-1));
            // cout<<"Expression received from client :"<<inputbuf<<'\n';
            
            // // n=recv(clientfd,&inputbuf,sizeof(inputbuf),0);
            // // n = write(clientfd,inputbuf,strlen(inputbuf));
            // // cout<<"Expression received from client: "<<inputbuf<<'\n';
            // int answer= evaluate(inputbuf);
            // cout<<"Answer: "<<answer<<'\n';
            // char result[MAX_INPUT_SIZE];
            // sprintf(result, "%d", answer);
            // n = write(clientfd, inputbuf, strlen(inputbuf));
            // // send(clientfd,&result, sizeof(result),0);
            // char buffer[1024];
            recv(clientfd,&inputbuf,sizeof(inputbuf),0);
            cout<<"Client socket sent message: "<<inputbuf<<'\n';
            int answer=evaluate(inputbuf);
            cout<<"Sending reply: "<<answer<<'\n';
            char result[1024];
            sprintf(result,"%d",answer);
            send(clientfd,&result, sizeof(result),0);

        }
        while(1);
    }
    return 0;
}
