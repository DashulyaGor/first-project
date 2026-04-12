#include <stdio.h>

#define N 9

// Вспомогательная функция: проверяет, содержит ли массив числа 1..9 ровно по одному разу
int is_valid(int arr[9]) {
    int seen[10] = {0};  // seen[i] = 1, если цифра i уже встречалась

    for (int i = 0; i < 9; i++) {
        int num = arr[i];
        if (num < 1 || num > 9 || seen[num]) {
            return 0;  // неверное число или дубликат
        }
        seen[num] = 1;
    }
    return 1;
}

int main() {
    int grid[N][N];

    // Чтение судоку
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Проверка всех строк
    for (int i = 0; i < N; i++) {
        if (!is_valid(grid[i])) {  // grid[i] — i-я строка
            printf("NO\n");
            return 0;
        }
    }

    // Проверка всех столбцов
    for (int j = 0; j < N; j++) {
        int col[9];
        for (int i = 0; i < N; i++) {
            col[i] = grid[i][j];
        }
        if (!is_valid(col)) {
            printf("NO\n");
            return 0;
        }
    }

    // Проверка всех блоков 3x3
    for (int block = 0; block < N; block++) {
        int bx = (block / 3) * 3;  // начальная строка блока
        int by = (block % 3) * 3;  // начальный столбец блока
        int temp[9];
        int idx = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp[idx++] = grid[bx + i][by + j];
            }
        }

        if (!is_valid(temp)) {
            printf("NO\n");
            return 0;
        }
    }

    // Если всё прошло проверку
    printf("YES\n");
    return 0;
}