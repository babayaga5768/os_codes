#include<bits/stdc++.h>
using namespace std;

int main(){
  int n,q, total_burst=0; cin>>n>>q;
  multimap<int,int> process;

  for(int i=0;i<n;++i){
    int arr, burst; cin>>arr>>burst;
    process.insert(make_pair(arr,burst));
    total_burst+=burst;
  }

  int cur=0, tat=0;

  while(!process.empty()){
    int flag=0;
    for(auto it=process.begin();it!=process.end();){
      if(cur>=it->first){
        flag=1;
      }else{
        break;
      }
      int pr=min(q, it->second);
      cur+=pr; it->second-=pr;
      if(it->second<=0){
        tat+=cur-it->first;
        it=process.erase(it);
      }
      else ++it;
    }
    if(flag==0 && !process.empty())cur++;
  }

  int wait=tat-total_burst;
  printf("Waiting time is: %0.4f\n", (wait*1.0)/n);
}