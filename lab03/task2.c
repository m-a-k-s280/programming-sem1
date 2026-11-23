#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4

void print_matrix(int mat[N][N]) {
    // Row-Major Order: зовнішній цикл по рядках, внутрішній по стовпцях
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%6d", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int matrix[N][N];

    srand((unsigned int)time(NULL));

    // Заповнення матриці (Row-Major Order)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 99 + 1;
        }
    }

    printf("Вихідна матриця (%dx%d):\n", N, N);
    print_matrix(matrix);

    // Транспонування "на місці" (обхід лише верхнього трикутника над головною діагоналлю)
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }

    printf("\nТранспонована матриця:\n");
    print_matrix(matrix);

    return 0;
}