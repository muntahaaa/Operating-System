#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ROWS1 2
#define COLS1 4
#define ROWS2 4
#define COLS2 3

int result[ROWS1][COLS2];

void multiply(int matA[ROWS1][COLS1], int matB[ROWS2][COLS2], int i) {
    for (int j = 0; j < COLS2; j++) {
        result[i][j] = 0;
        for (int k = 0; k < COLS1; k++) {
            result[i][j] += matA[i][k] * matB[k][j];
        }
    }
}

int main() {
    int matrix1[ROWS1][COLS1] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };

    int matrix2[ROWS2][COLS2] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    FILE *file = fopen("result1.txt", "w+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ROWS1; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            multiply(matrix1, matrix2, i);
            fprintf(file, "%d %d %d\n", result[i][0], result[i][1], result[i][2]);
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i < ROWS1; i++) {
        wait(NULL);
    }

    rewind(file);
    printf("Result Matrix (C):\n");
    int res[ROWS1][COLS2];
    for (int i = 0; i < ROWS1; i++) {
        fscanf(file, "%d %d %d", &res[i][0], &res[i][1], &res[i][2]);
        printf("%d\t%d\t%d\n", res[i][0], res[i][1], res[i][2]);
    }
    fclose(file);

    return 0;
}
