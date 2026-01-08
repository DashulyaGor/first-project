#include <stdio.h>
#include <stdlib.h>

#define MAX 1300001  // Максимальное значение числа

int main() {
    // Шаг 1: Выделяем память под массив is_prime
    int *is_prime = (int*)malloc(MAX * sizeof(int));
    if (is_prime == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    // Инициализация: 0 и 1 — не простые
    is_prime[0] = 0;
    is_prime[1] = 0;
    for (int i = 2; i < MAX; i++) {
        is_prime[i] = 1;  // Сначала считаем все >=2 простыми
    }

    // Решето Эратосфена
    for (int i = 2; i * i < MAX; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAX; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    // Шаг 2: Считываем входные данные
    int n;
    scanf("%d", &n);

    // Читаем n чисел и выводим только простые
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x >= 0 && x < MAX && is_prime[x]) {
            printf("%d ", x);
        }
    }
    printf("\n");

    // Освобождаем динамическую память
    free(is_prime);

    return 0;
}
