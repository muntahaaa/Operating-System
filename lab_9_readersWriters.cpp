#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

sem_t rw_mutex;
sem_t mtx;
int read_count;

void *writer(void *arg)
{
    int writer_id = *((int *)arg);

    FILE *file = fopen("example.txt", "a");
    if (file == nullptr)
    {
        cout << "Cannot open file for writing." << endl;
        return NULL;
    }

    sem_wait(&rw_mutex);

    fprintf(file, "Good morning from writer %d!\n", writer_id);
    cout << "Writer " << writer_id << " has written in the file" << endl;
    fclose(file);
    sem_post(&rw_mutex);

    return NULL;
}

void *reader(void *arg)
{
    int reader_id = *((int *)arg);

    FILE *file = fopen("example.txt", "r");
    if (file == nullptr)
    {
        cout << "Cannot open file for reading." << endl;
        return NULL;
    }

    sem_wait(&mtx);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);
    sem_post(&mtx);

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != nullptr)
    {
        cout << "Reader " << reader_id << " reads from file: " << buffer;
    }

    fclose(file);

    sem_wait(&mtx);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);
    sem_post(&mtx);

    return NULL;
}

int main()
{
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mtx, 0, 1);
    read_count = 0;
    pthread_t readers1, readers2, writers1, writers2;

    int reader_id1 = 1;
    int reader_id2 = 2;
    int writer_id1 = 1;
    int writer_id2 = 2;

    pthread_create(&writers1, NULL, writer, &writer_id1);
    pthread_create(&readers1, NULL, reader, &reader_id1);
    pthread_create(&writers2, NULL, writer, &writer_id2);
    pthread_create(&readers2, NULL, reader, &reader_id2);

    pthread_join(writers1, NULL);
    pthread_join(readers1, NULL);
    pthread_join(writers2, NULL);
    pthread_join(readers2, NULL);

    sem_destroy(&rw_mutex);
    sem_destroy(&mtx);

    return 0;
}
