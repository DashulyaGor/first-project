#include <stdio.h>

#define N 10
// Функция получает сумму двух матриц
void sum(int rows, int cols, int a[10][10], int b[10][10], int c[10][10]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);  // читаем размеры матрицы

    int a[N][N];  // объявляем матрицу переменного размера
    int b[N][N];
    int c[N][N];

    // Чтение элементов матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    while (getchar() != '\n');

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    // запрос суммы
    sum(n, m, a, b, c);

    // Печать результата
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}