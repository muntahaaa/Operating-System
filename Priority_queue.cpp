#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int priority;
    int burst;
};

bool operator<(const Process &a, const Process &b)
{

    return a.priority < b.priority;
}

int main()
{
    freopen("input.txt", "r", stdin);
    vector<Process> sortedProcess;
    vector<int> turnAround, waiting;
    int turnAround_sum = 0, waiting_sum = 0;
    int processNum = 5;
    turnAround.push_back(0);
    waiting.push_back(0);
    for (int i = 0; i < processNum; i++)
    {
        string process = "P[" + to_string(i + 1) + "]";
        int prio, bur;
        cin >> bur >> prio;
        sortedProcess.push_back({process, prio, bur});
    }
    sort(sortedProcess.begin(), sortedProcess.end());

    for (int i = 1; i <= processNum; i++)
    {
        turnAround.push_back(turnAround[i - 1] + sortedProcess[i - 1].burst);
        waiting.push_back(turnAround[i] - sortedProcess[i - 1].burst);
        turnAround_sum += turnAround[i];
        waiting_sum += waiting[i];
    }

    // for (const auto &process : sortedProcess)
    // {
    //     cout << "Name: " << process.pid << ", Priority: " << process.priority << ", Burst Time: " << process.burst << endl;
    // }

    cout << "Gantt chart for Priority Queue algorithm: " << endl;
    cout << "|";
    for (int i = 0; i < processNum; i++)
    {
        cout << "--" << sortedProcess[i].pid << "--|";
    }
    cout << endl;
    for (auto t : turnAround)
    {
        printf("%-9d", t);
    }
    cout << endl
         << endl;
    printf("%s  %s\t%s\n", "Process ID",
           "Turnaround Time", "Waiting Time");

    for (int i = 1; i <= processNum; i++)
    {
        cout << sortedProcess[i - 1].pid;
        printf(" %15d %20d\n",
               turnAround[i], waiting[i]);
    }

    cout << endl
         << endl;
    cout << "Average turnaround time: " << (double)turnAround_sum / processNum << endl;
    cout << "Average waiting time: " << (double)waiting_sum / processNum << endl;
}