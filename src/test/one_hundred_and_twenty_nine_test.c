#include <stdio.h>
#include <string.h>

#define MAX_N 67

int main() {
    int n;
    scanf("%d", &n);

    // Два массива для хранения текущего и следующего ряда
    unsigned long long row1[MAX_N] = {0};
    unsigned long long row2[MAX_N] = {0};

    // Указатели на текущий и следующий ряд
    unsigned long long *current = row1;
    unsigned long long *next = row2;

    // Инициализация: C(0,0) = 1
    current[0] = 1;

    // Построение рядов от 0 до n
    for (int i = 1; i <= n; i++) {
        // Вычисляем i-й ряд через (i-1)-й (current)
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                next[j] = 1;
            } else {
                next[j] = current[j-1] + current[j];
            }
        }

        // Меняем местами указатели: next становится current для следующей итерации
        unsigned long long *temp = current;
        current = next;
        next = temp;
    }

    // После цикла current указывает на ряд n
    // Выводим коэффициенты через пробел
    for (int k = 0; k <= n; k++) {
        printf("%llu", current[k]);
        if (k < n) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}