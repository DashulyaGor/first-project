#include <stdio.h>

#define MAX_N 100
int memo[MAX_N];      // Массив для кэширования значений
int call_count = 0;         // Счётчик вызовов

int fib(int n, int depth) {
    call_count++;
    printf("%-*c call fib(%d)\n", depth, '>', n);

    // Проверяем, уже ли вычисляли fib(n)
    if (memo[n] != -1) {
        printf("%-*c memo[%d] = %d (cached)\n", depth, '>', n, memo[n]);
        return memo[n];
    }

    int res;

    // Базовый случай
    if (n == 0 || n == 1) {
        res = 1;
        printf("%-*c f(0) = f(1) = 1\n", depth, '>');
    } else {
        // Рекурсивные вызовы с мемоизацией
        res = fib(n - 1, depth + 4) + fib(n - 2, depth + 4);
    }

    // Запоминаем результат
    memo[n] = res;
    printf("%-*c fib(%d) = %d\n", depth, '>', n, res);

    return res;
}

int main() {
    int n;
    printf("Введите n: ");
    scanf("%d", &n);

    // Проверка диапазона
    if (n < 0 || n >= MAX_N) {
        printf("n должно быть в диапазоне [0, %d)\n", MAX_N);
        return 1;
    }

    // Инициализация массива memo значением -1 (не вычислено)
    for (int i = 0; i < MAX_N; i++) {
        memo[i] = -1;
    }

    int result = fib(n, 0);
    printf("Result: fib(%d) = %d\n", n, result);
    printf("Total function calls: %d\n", call_count);

    return 0;
}