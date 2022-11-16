#include <bits/stdc++.h>
using namespace std;
//for main memory
void InsertPage(int memoryReq, vector<int>MainMem, int frameNo){
    if(find(MainMem.begin(), MainMem.end(), memoryReq) != MainMem.end()){
        MainMem.erase(remove(MainMem.begin(), MainMem.end(), memoryReq), MainMem.end());
        MainMem.push_back(memoryReq);
    } else {
        if(MainMem.size() == (frameNo+1)){
            MainMem.erase(MainMem.begin());
        }
        MainMem.push_back(memoryReq);
    }
}
//for tlb
void InsertPage(int memoryReq, int frameNo, int tlbSize, unordered_map<int, int> tlb){
    if(tlb.size() == tlbSize+1){
        tlb.erase(tlb.begin());
    }
    tlb.insert({memoryReq, frameNo});
}

int main(int argc, char*argv[]){
    ofstream fout("res.txt");
    if(argc!=5){
        fout<<"No. of arguments given is invalid"<<'\n';
        return 0;
    }
    int numOfProcesses = atoi(argv[1]);
    int frameNo = atoi(argv[3]);
    vector<int> MainMem(frameNo+1);
    int tlbSize = atoi(argv[4]);
    int PageNo = atoi(argv[2]);
    for(int i=1;i<numOfProcesses+1;i++){
        fout<<"Process no. "<<i<<'\n';
        unordered_map<int, int>tlb;
        int reqpages=1+rand()%PageNo;
        
        unordered_map<int, pair<int, int>> PageTable; 
        for(int j=0;j<PageNo;j++){
            PageTable.insert({j, {-1, 0}});
        }
        vector<int> refString;
        int lengthRefString = 2*reqpages+rand()%(10*reqpages+1);
        for(int j=0;j<lengthRefString;j++){
            refString.push_back(rand()%PageNo);
            sleep(2);
        }
        int pagefaults=0;
        for(int it=0;i<refString.size();it++){
            if(tlb.find(refString[it])!=tlb.end()){
                fout<<"Process "<<i-1<<" : for page reference "<<refString[it]<<", TLB hrefString[it] wrefString[it]h frame number "<<tlb[refString[it]]<<'\n';
            }
            else if(PageTable.find(refString[it])!=PageTable.end()){
                if(PageTable[refString[it]].second){
                    fout<<"Process "<<i-1<<" : for page reference "<<refString[it]<<", TLB miss -> "<<"Page table valid wrefString[it]h frame number "<<PageTable[refString[it]].first<<'\n';
                    if(tlb.size()<tlbSize){
                        tlb.insert({refString[it], PageTable[refString[it]].first});
                    } 
                    else{
                        tlb.erase(tlb.begin());
                        tlb.insert({refString[it], PageTable[refString[it]].first});
                    }
                }
                else{
                    pagefaults++;
                    InsertPage(refString[it], MainMem, frameNo);
                    InsertPage(refString[it], frameNo, tlbSize, tlb);
                    PageTable[refString[it]].first = MainMem[MainMem.size()-1];
                    fout<<"Process "<<i<<" : for page reference "<<refString[it]<<", TLB miss "<<"Page table invalid wrefString[it]h frame number "<<PageTable[refString[it]].first<<'\n';
                }
            }
            
        }
     
    fout<<"Number of page faults for process "<<i<<" : "<<pagefaults<<'\n';   

    }
}




   