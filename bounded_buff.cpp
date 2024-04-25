#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#define MaxItems 5
#define BufferSize 5
using namespace std;

sem_t full;
sem_t emp;
int in = 0;
int out = 0;

int buffer[BufferSize];
pthread_mutex_t mtx;

void *producer(void *pno)
{
    int item;
    for (int i = 0; i < MaxItems; i++)
    {
        item = rand() % 20;
        sem_wait(&emp);
        pthread_mutex_lock(&mtx);
        buffer[in] = item;
        printf("Producer %d Insert item %d at %d\n",
               *((int *)pno), item, in);
        in = (in + 1) % BufferSize;
        pthread_mutex_unlock(&mtx);
        sem_post(&full);
    }
}

void *consumer(void *cno)
{
    sem_wait(&full);
    pthread_mutex_lock(&mtx);
    int item = buffer[out];
    printf("Consumer %d Remove item %d at %d\n",
           *((int *)cno), item, out);
    out = (out + 1) % BufferSize;
    pthread_mutex_unlock(&mtx);
    sem_post(&emp);
}

int main()
{
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mtx, NULL);
    sem_init(&emp, 0, BufferSize);
    sem_init(&full, 0, 0);

    int a[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        for (int i = 0; i < 5; i++)
        {
            int *arg = &a[i]; // Pointer to the argument (producer number)
            pthread_create(&pro[i], NULL, producer, (void *)arg);
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int i = 0; i < 5; i++)
        {
            int *arg = &a[i]; // Pointer to the argument (consumer number)
            pthread_create(&con[i], NULL, consumer, (void *)arg);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(pro[i], NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(con[i], NULL);
    }
    pthread_mutex_destroy(&mtx);
    sem_destroy(&emp);
    sem_destroy(&full);
}