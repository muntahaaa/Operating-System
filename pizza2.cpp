#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <thread>

#define S 4
#define Student 10

using namespace std;

sem_t pizza, deliver;
pthread_mutex_t mtx;
int num_slices;
bool must_study, employed;
int student_no = 1;
void study();

void *delivery(void *arg)
{
    while (employed)
    {
        pthread_mutex_lock(&mtx);
        num_slices = S;
        pthread_mutex_unlock(&mtx);
        for (int i = 0; i < S; i++)
        {
            sem_post(&pizza);
        }
        sem_post(&deliver);
        cout << "pizze preapred, slice= " << num_slices << endl;
        employed = false;
    }
    if (student_no <= Student)
        study();
    return NULL;
}

void study()
{

    num_slices = S;
    must_study = true;
    while (must_study)
    {
        if (num_slices > 0)
        {
            pthread_mutex_lock(&mtx);
            cout << "student no " << student_no << " is studying " << endl;

            if (student_no == Student)
                must_study = false;
            student_no++;
            // student_no=student_no%Student;
            num_slices--;
            pthread_mutex_unlock(&mtx);
            sem_wait(&pizza);
        }
        else
        {
            employed = true;
            cout << "order pizza " << endl;
            sem_wait(&deliver);
            pthread_t delivery_thread_id;
            pthread_create(&delivery_thread_id, NULL, delivery, NULL);
            pthread_join(delivery_thread_id, NULL);
            must_study = false;
        }
    }
    must_study = true;
}

int main()
{
    pthread_mutex_init(&mtx, NULL);
    sem_init(&pizza, 0, S);
    sem_init(&deliver, 0, 1);
    study();
    pthread_mutex_destroy(&mtx);
    sem_destroy(&pizza);
    sem_destroy(&deliver);

    return 0;
}