#include <bits/stdc++.h>
using namespace std;
#define row 5
#define col 3

int allocation[][col] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}};
int max_need[][col] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {4, 2, 2},
    {5, 3, 3}};
int remaining_need[row][col];
vector<int> safe;
int available[col] = {0};
bool finished[row] = {false};
bool flag;
int main()
{
    int total[col] = {10, 5, 7};
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            remaining_need[i][j] = max_need[i][j] - allocation[i][j];
            available[j] += allocation[i][j];
        }
    }
    for (int i = 0; i < col; i++)
    {
        available[i] = total[i] - available[i];
        cout << available[i] << endl;
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << remaining_need[i][j] << " ";
        }
        cout << endl;
    }

    while (safe.size() < row)
    {
        bool found_process = false;
        for (int i = 0; i < row; i++)
        {
            if (!finished[i])
            {
                bool can_allocate = true;
                for (int j = 0; j < col; j++)
                {
                    if (remaining_need[i][j] > available[j])
                    {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate)
                {
                    for (int j = 0; j < col; j++)
                    {
                        available[j] += allocation[i][j];
                    }
                    safe.push_back(i);
                    finished[i] = true;
                    found_process = true;
                }
            }
        }
        if (!found_process)
        {
            cout << "System is in an unsafe state." << endl;
            return 0;
        }
    }

    cout << "Safe sequence: ";
    for (int i : safe)
    {
        cout << "P" << i + 1 << " ";
    }
    cout << endl;
}