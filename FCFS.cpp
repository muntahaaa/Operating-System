#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    int process_num=5,val,turnAround_sum=0,waiting_sum=0;
    vector<int>burst,priority,waiting,turnAround;
    burst.push_back(0);
    turnAround.push_back(0);
    waiting.push_back(0);

    for(int i=1;i<=process_num;i++){
       cin>>val;
       burst.push_back(val);
       cin>>val;
       priority.push_back(val);
       turnAround.push_back(burst[i]+turnAround[i-1]);
       waiting.push_back(turnAround[i]-burst[i]);
       turnAround_sum+=turnAround[i];
       waiting_sum+=waiting[i];
    }

    cout<<"Gantt chart for FCFS algorithm: "<<endl;
    cout<<"| ";
    for(int i=1;i<=process_num;i++){
        cout<<"---P"<<i<<"---|";
    }
    cout<<endl;
    for(auto t: turnAround){
        printf("%-9d",t);
    }
     cout<<endl<<endl;
    printf("%s  %s\t%s\n","Process ID",
    "Turnaround Time","Waiting Time");

    for(int i=1;i<=process_num;i++){
         printf("P%d %15d %20d\n",i,
         turnAround[i],waiting[i]);
    }

    cout<<endl<<endl;
    cout<<"Average turnaround time: "<<(double)turnAround_sum/process_num<<endl;
    cout<<"Average waiting time: "<<(double)waiting_sum/process_num<<endl;





}