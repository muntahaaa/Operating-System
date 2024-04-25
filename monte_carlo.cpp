#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int circle ;
int square ;

void *runner(void *param) {
    double x, y;

    for (int i = 0; i < 10000; i++) {
        x = (double)rand() / RAND_MAX * 2.0-1; //ranges in between [-1,1]
        y = (double)rand() / RAND_MAX * 2.0-1;
        
        double distance = sqrt(x * x + y * y);

        if (distance <= 1) {
            circle++;
        }
        square++;
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    srand(time(NULL)); // Seed the random number generator

    pthread_create(&tid, &attr, runner, NULL);
    pthread_join(tid, NULL);

    float result = 4.0 * circle / square;

    printf("square = %d, circle = %d ,The value of pi = %f\n",square,circle, result);

    return 0;
}
