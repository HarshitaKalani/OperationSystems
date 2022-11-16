#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include <fcntl.h>
#include <filesystem>
#include <cstdlib>
namespace fs = std::filesystem;
using namespace std;

// struct range_msg{
//     int min;
//     int max;

// }range_msg;
int range_msg[2];
int main(){
    key_t key, key_rnd;
    int msg_id, msg_rnd;
    srand(time(0)); //helps generate a random number by seeding rand with a starting value.
    key = ftok("server.cpp", 65);
    msg_id=msgget(key, 0666 | IPC_CREAT);
    msgrcv(msg_id, &range_msg, sizeof(range_msg), 0, 0);
    int mx= range_msg[1];
    int mn= range_msg[0];
    cout<<"Range: "<<mn<<" "<<mx<<'\n';
    int rnd_int = rand()%(mx-mn+1)+mn;
    key_rnd=ftok("server_receive", 65);
    msg_rnd = msgget(key_rnd, 0666 | IPC_CREAT);
    msgsnd(msg_rnd, &rnd_int, sizeof(rnd_int), 0);
    return 0;
}