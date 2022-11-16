#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/wait.h>

#include <fcntl.h>
#include <filesystem>
#include <cstdlib>
using namespace std;
namespace fs = std::filesystem;

int range_msg[2];
int main(int argc, char*argv[]){
    for(int i=1;i<argc;i++){
        string s=argv[i];
        std::filesystem::copy("client.cpp",s+".cpp");
    }
    // cout<<"length of argc:"<< argc<<'\n';
    vector<int>score(argc-1,0);
    vector<int>rnd_nos(argc-1, 0);
    key_t key, key_rnd;
    int msg_id, msg_rnd;
    key=ftok("server.cpp",65); //ftok is used to generate a unique key
    key_rnd=ftok("server_receive",65);
    msgctl(msg_id, IPC_RMID, NULL); //msgctl() performs various operations on a queue. Generally it is used to destroy message queue.
    msg_id=msgget(key, 0666 | IPC_CREAT); //msgget() either returns the message queue identifier for a newly created meassage queue or returns the identifiers for a queue which exists with the same key value.
    msg_rnd=msgget(key_rnd, 0666 | IPC_CREAT);
    while(true){
        cout<<"Enter the range of numbers to be generated: ";
        int mn,mx;
        cin>>mn>>mx;
        range_msg[0]=mn;
        range_msg[1]=mx;
        cout<<"Range: "<<range_msg[0]<<" "<<range_msg[1]<<'\n';
        for(int i=1;i<argc;i++){
            msgsnd(msg_id, &range_msg, sizeof(range_msg), 0); //data is placed on to a message queue by calling msgsnd()
            system(("g++ "+string(argv[i])+".cpp -o "+string(argv[i])).c_str());
            system(("./"+string(argv[i])+" &").c_str());
            wait(NULL);
        }
        sleep(2);
        for(int i=1;i<argc;i++){
            int rnd_int;
            msgrcv(msg_rnd, &rnd_int, sizeof(rnd_int),0,0);
            cout<<"Random number received from "<<argv[i]<<" : "<<rnd_int<<endl;
            rnd_nos[i-1]=rnd_int;
            wait(NULL);
        }

        srand(time(0));
        int gen=(rand()%(mx-mn+1))+mn;
        cout<<"Random number generated: "<<gen<<'\n';
        double deno=0;
        for(int i=0;i<argc;i++){
            deno+=(rnd_nos[i]-gen)*(rnd_nos[i]-gen);
        }
        int min_delta_process=-1;
        double min_delta=INT_MAX;
        for(int i=1;i<argc;i++){
            double delta=(double) abs(rnd_nos[i]-gen)/ (double) deno;
            if(delta<min_delta){
                min_delta_process=i;
                min_delta=delta;
            }
        }
        cout<<"Client "<<argv[min_delta_process]<<" has minimum delta"<<'\n';
        cout<<"Winner of this round is "<<argv[min_delta_process]<<" hence gets 5 points"<<"\n";
        score[min_delta_process-1]+=5;
        for(int i=1;i<argc;i++){
            if(score[i-1]>=50){
                cout<<"Client "<<argv[i]<<" is the winner"<<'\n';
                msgctl(msg_id, IPC_RMID, NULL);
                msgctl(msg_rnd, IPC_RMID, NULL);
                exit(0);
            } 
        }
        cout<<"Client  "<<"Score"<<'\n';
        for(int i=1;i<argc;i++){
            cout<<argv[i]<<"    "<< score[i-1]<<'\n';
        }
    }
    msgctl(msg_id, IPC_RMID, NULL);
    msgctl(msg_rnd, IPC_RMID, NULL);
    return 0;
}   