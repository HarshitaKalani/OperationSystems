#include <bits/stdc++.h>
using namespace std;

void fifo(vector<int> refString, int frameNo, ofstream &fout){
    unordered_set<int>s;
    queue<int> q;
    int pagefaults=0;
    for(int i=0;i<refString.size();i++){
        if(s.size()<frameNo){
            if(s.find(refString[i])==s.end()){
                s.insert(refString[i]);
                pagefaults++;
                fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB miss -> "<<"Page fault -> "<<"Page table valid wrefString[i]h frame number "<<s.size()-1<<'\n';
                q.push(refString[i]);
            }
            else{
                fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB hit -> "<<"Page table valid wrefString[i]h frame number "<<s.size()-1<<'\n';
            }
            
        } else {
            if(s.find(refString[i])==s.end()){
                int val = q.front();
                q.pop();
                s.erase(val);
                s.insert(refString[i]);
                q.push(refString[i]);
                pagefaults++;
                fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB miss -> "<<"Page fault -> "<<"Page table valid wrefString[i]h frame number "<<s.size()-1<<'\n';

            }
            else{
                fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB hit -> "<<"Page table valid wrefString[i]h frame number "<<s.size()-1<<'\n';
            }
        }
    }
    fout<<"FIFO page replacement algorithm: "<<pagefaults<<'\n';
    fout<<'\n';
}

void lru(vector<int>refString, int frameNo, ofstream&fout){
    unordered_set<int>s;
    unordered_map<int, int>m;
    int pagefaults=0;
    for(int i=0;i<refString.size();i++){
        if(s.size()<frameNo){
            if(s.find(refString[i])==s.end()){
                s.insert(refString[i]);
                pagefaults++;
                fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB miss -> "<<"Page fault -> "<<"Page table valid wrefString[i]h frame number "<<s.size()-1<<'\n';
            }
            else{
                fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB hit wrefString[i]h frame number "<<m[refString[i]]<<'\n';
            }
            m[refString[i]]=i;
        }
        else{
            if(s.find(refString[i])==s.end()){
                int lru=INT_MAX, val;
                for(auto it: s){
                    if(m[it]<lru){
                        lru=m[it];
                        val=it;
                    }
                }
                s.erase(val);
                s.insert(refString[i]);
                pagefaults++;
                fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB miss -> "<<"Page fault -> "<<"Page table valid wrefString[i]h frame number "<<m[refString[i]]<<'\n';
            }
            else{
                fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB hit wrefString[i]h frame number "<<m[refString[i]]<<'\n';
            }
            m[refString[i]]=i;
        }
    }
    fout<<"Page faults for lru page replacement algorithm: "<<pagefaults<<'\n';
    fout<<'\n';
}

void optimal(vector<int>refString, int frameNo, ofstream&fout){
    vector<int>frame;
    int hit=0;
    for(int i=0;i<refString.size();i++){
        
        if(find(frame.begin(), frame.end(), refString[i])!=frame.end()){
            hit++;
        }
        if(frame.size()<frameNo){
            frame.push_back(refString[i]);
            fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB miss -> "<<"Page fault -> "<<"Page table valid wrefString[i]h frame number "<<frame.size()-1<<'\n';

        }
        else{
            fout<<"Process "<<i<<" : for page reference "<<refString[i]<<", TLB hit -> "<<"Page table valid wrefString[i]h frame number "<<frame.size()-1<<'\n';
            int index=-1, farthest=0;
            for(int j=0;j<frameNo;j++){
                int k;
                for(k=i;k<refString.size();k++){
                    if(frame[j]==refString[k]){
                        if(k>farthest){
                            farthest=k;
                            index=j;
                        }
                        break;
                    }
                }
                if(k==refString.size()){
                    index=j;
                    break;
                }
            }
            frame[index]=refString[i];
        }
          
    }
    fout << "Page faults for optimal page replacement algorithm : " << hit << endl;
    fout<<'\n';
}
int main(){
    //call fifo
    ofstream fout("res.txt");
   
    int frameNo;
    cout<<"Enter the number of frames: ";
    cin>>frameNo;
    vector<int> refString;
    int n;
    cout<<"Enter the number of page references: ";
    cin>>n;
    cout<<"Enter the page references: ";
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        refString.push_back(x);
    }

    fout<<"FIFO page replacement algorithm: "<<'\n';
    fifo(refString, frameNo, fout);
    fout<<"LRU page replacement algorithm: "<<'\n';
    lru(refString, frameNo, fout);
    fout<<"Optimal page replacement algorithm: "<<'\n';
    optimal(refString, frameNo, fout);
    return 0;

}