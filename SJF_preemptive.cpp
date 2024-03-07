#include <bits/stdc++.h>
using namespace std;

int processNum = 6;

struct Process
{
    string pid;
    int burst;
    int arrival;
    int remaining_burst;
    int waiting;
    int turnAround;
};

bool compareProcess(Process a, Process b)
{
    return a.arrival < b.arrival;
}
double calculateAverage(const std::vector<int> &numbers)
{
    if (numbers.empty())
    {
        std::cerr << "Error: Cannot calculate average for an empty vector." << std::endl;
        return 0.0;
    }

    int sum = 0;
    for (int number : numbers)
    {
        sum += number;
    }

    return static_cast<double>(sum) / numbers.size();
}

int main()
{

    freopen("input.txt", "r", stdin);
    vector<Process> process(processNum);
    vector<string> processNo;
    vector<int> turnAroundTime;
    vector<int> waitingAvg;
    vector<int> turnAroundAvg;

    int value, wait = 0, turn = 0;
    string currentProcess;

    for (int i = 0; i < processNum; i++)
    {
        cin >> value;
        process[i].burst = value;
        cin >> value;
        process[i].arrival = value;
        process[i].pid = "p" + to_string(i + 1);
    }

    sort(process.begin(), process.end(), compareProcess);

    for (auto &p : process)
    {
        p.remaining_burst = p.burst;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < processNum)
    {
        int minRemainingBurst = INT_MAX;
        int nextProcessID = -1;

        for (int i = 0; i < processNum; i++)
        {
            if (process[i].arrival <= currentTime && process[i].remaining_burst > 0)
            {
                if (process[i].remaining_burst < minRemainingBurst)
                {
                    minRemainingBurst = process[i].remaining_burst;
                    nextProcessID = i;
                }
            }
        }

        if (nextProcessID != -1)
        {
            if (currentProcess == "idle")
            {
                processNo.push_back("idle");
                turnAroundTime.push_back(currentTime);
            }

            currentProcess = process[nextProcessID].pid;
            process[nextProcessID].remaining_burst--;
            currentTime++;

            if (process[nextProcessID].remaining_burst == 0)
            {
                completedProcesses++;
                processNo.push_back(process[nextProcessID].pid);
                turnAroundTime.push_back(currentTime);

                turnAroundAvg.push_back(currentTime - process[nextProcessID].arrival);
                waitingAvg.push_back(turnAroundAvg[nextProcessID] - process[nextProcessID].burst);
                if (process[nextProcessID + 1].arrival > currentTime)
                    currentProcess = "idle";
            }
        }
        else
        {

            currentTime++;
        }
    }

    cout << "Gantt chart for preemptive SJF algorithm :" << endl;
    cout << "|";
    for (auto p : processNo)
    {
        cout << "--- " << p << " ---|";
    }
    cout << endl;

    printf("%-11d", 0);
    for (auto t : turnAroundTime)
    {
        printf("%-11d", t);
    }

    cout << endl
         << endl;
    cout << "Average turnaround time: " << calculateAverage(turnAroundAvg) << endl;
    cout << "Average waiting time: " << calculateAverage(waitingAvg) << endl;

    return 0;
}
