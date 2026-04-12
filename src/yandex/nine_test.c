#include <stdio.h>
/*
int move_ways(int n, int m) {
    char grid[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {  // Свободная клетка
                // Попробуем поставить горизонтально: (i,j) и (i,j+1)
                if (j + 1 < m && grid[i][j + 1] == '.') {
                    grid[i][j] = '#';
                    grid[i][j + 1] = '#';
                }
                // Иначе — вертикально: (i,j) и (i+1,j)
                else if (i + 1 < n && grid[i + 1][j] == '.') {
                    grid[i][j] = '#';
                    grid[i + 1][j] = '#';
                }
            }
        }
    }
}
*/
int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Создаём сетку
    char grid[100][100];  // Предполагаем, что n, m <= 100

    // Инициализируем все клетки как свободные
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%hhd", &grid[i][j]);
        }
    }

    // Вывод результата
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}