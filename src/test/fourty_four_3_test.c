#include <stdio.h>

int call_count = 0;

int fib_iter(int n, int depth) {
    // Имитируем "вызов" — увеличиваем счётчик
    call_count++;

    printf("%-*c call fib(%d)\n", depth, '>', n);

    // Базовые случаи
    if (n == 0 || n == 1) {
        printf("%-*c f(0) = f(1) = 1\n", depth, '>');
        return 1;
    }

    // Итеративное вычисление fib(n)
    int a = 1, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    printf("%-*c fib(%d) = %d\n", depth, '>', n, b);
    return b;
}

int main() {
    int n;
    printf("Введите n: ");
    scanf("%d", &n);

    int result = fib_iter(n, 0);
    printf("Result: fib(%d) = %d\n", n, result);
    printf("Total 'calls': %d\n", call_count);

    return 0;
}
