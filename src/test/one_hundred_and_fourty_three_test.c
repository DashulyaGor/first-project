#include <stdio.h>

// Функция умножает матрицу a[rows][cols] на число k
void number_mult(int k, int rows, int cols, int a[][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            a[i][j] *= k;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);  // читаем размеры матрицы

    int a[n][m];  // объявляем матрицу переменного размера

    // Чтение элементов матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int k;
    scanf("%d", &k);  // читаем множитель

    // Умножаем матрицу на k
    number_mult(k, n, m, a);

    // Печать результата
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}