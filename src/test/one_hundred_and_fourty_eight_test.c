#include <stdio.h>

#define N_MAX 100
#define SIZE (N_MAX + 2)  // +1 сверху/снизу и слева/справа

char grid[SIZE][SIZE];  // поле с рамкой
int n;

// Рекурсивная функция заливки фигуры
void fill(int i, int j) {
    // Если не является частью фигуры — выходим
    if (grid[i][j] != '*') {
        return;
    }

    // Перекрашиваем текущую клетку
    grid[i][j] = '.';  // "удаляем" фигуру, чтобы не найти её снова

    // Рекурсивно заливаем соседей (по сторонам)
    fill(i - 1, j);  // вверх
    fill(i + 1, j);  // вниз
    fill(i, j - 1);  // влево
    fill(i, j + 1);  // вправо
}

int main() {
    // Чтение размера
    scanf("%d", &n);

    // Обнуление всей сетки (включая рамку)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = '.';
        }
    }

    // Чтение поля, помещаем его внутрь рамки: от (1,1) до (n,n)
    char line[N_MAX + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%100s", line);
        for (int j = 1; j <= n; j++) {
            grid[i][j] = line[j - 1];  // сдвиг индекса: line[0] -> grid[i][1]
        }
    }

    int figure_count = 0;

    // Проходим по основному полю (без рамки)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] == '*') {
                // Нашли новую фигуру
                fill(i, j);           // закрашиваем её целиком
                figure_count++;       // увеличиваем счётчик
            }
        }
    }

    printf("%d\n", figure_count);
    return 0;
}