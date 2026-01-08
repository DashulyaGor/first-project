#include <stdio.h>
#include <stdlib.h>

#define MAX 1300001  // Максимальное значение числа + 1

int main() {
    // Шаг 1: Решето Эратосфена до MAX - 1
    int is_prime[MAX];
    
    // Инициализация: сначала считаем все числа >=2 простыми
    is_prime[0] = 0;  // 0 — не простое
    is_prime[1] = 0;  // 1 — не простое
    for (int i = 2; i < MAX; i++) {
        is_prime[i] = 1;
    }

    // Выполняем решето
    for (int i = 2; i * i < MAX; i++) {
        if (is_prime[i]) {
            // Вычёркиваем все кратные i, начиная с i*i
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
        if (is_prime[x]) {
            printf("%d ", x);
        }
    }
    printf("\n");

    return 0;
}
