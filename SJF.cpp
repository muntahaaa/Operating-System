#include <bits/stdc++.h>
using namespace std;

int process_num = 5;

bool cmp(pair<string, int> &a, pair<string, int> &b)
{
    return a.second < b.second;
}

vector<pair<string, int>> sort(map<string, int> &M)
{
    vector<pair<string, int>> A;
    string key;
    int val;

    for (auto &it : M)
    {
        A.push_back(it);
    }

    sort(A.begin(), A.end(), cmp);

    return A;
}

int main()
{
    freopen("input.txt", "r", stdin);
    map<string, int> process;
    vector<pair<string, int>> sortedProcess;
    vector<int> turnAround, waiting, priority;
    int turnAround_sum = 0, waiting_sum = 0, value;

    turnAround.push_back(0);
    waiting.push_back(0);

    for (int i = 1; i <= process_num; i++)
    {
        int p;
        cin >> value;
        process["P[" + to_string(i) + "]"] = value;
        cin >> p;
        priority.push_back(p);
    }

    sortedProcess = sort(process);

    // Print the sorted map
    // cout << "Sorted Process pair vector:" << endl;
    // for (auto &it : sortedProcess)
    // {
    //     cout << it.first << ' ' << it.second << endl;
    // }

    for(int i=1;i<=process_num;i++){
       turnAround.push_back(sortedProcess[i-1].second+turnAround[i-1]);
       waiting.push_back(turnAround[i]-sortedProcess[i-1].second);
       turnAround_sum+=turnAround[i];
       waiting_sum+=waiting[i];
    }


      cout<<"Gantt chart for SJF algorithm: "<<endl;
    cout<<"|";
    for(int i=0;i<process_num;i++){
        cout<<"--"<<sortedProcess[i].first<<"--|";
    }
    cout<<endl;
    for(auto t: turnAround){
        printf("%-9d",t);
    }
     cout<<endl<<endl;
    printf("%s  %s\t%s\n","Process ID",
    "Turnaround Time","Waiting Time");

    for(int i=1;i<=process_num;i++){
        cout<<sortedProcess[i-1].first;
         printf(" %15d %20d\n",
         turnAround[i],waiting[i]);
    }

    cout<<endl<<endl;
    cout<<"Average turnaround time: "<<(double)turnAround_sum/process_num<<endl;
    cout<<"Average waiting time: "<<(double)waiting_sum/process_num<<endl;





    return 0;
}
