#include <stdio.h>

// Объявляем глобальную переменную для подсчёта числа вызовов
static int call_count = 0;

int fib(int n, int depth) {
    // Увеличим счётчик вызовов
    call_count++;
    
    printf("%-*c call fib(%d)\n", depth, '>', n);
    if (n == 0 || n == 1) {
        printf("%-*c f(0) = f(1) = 1\n", depth, '>');
        return 1;
    }
    int res = fib(n - 1, depth + 4) + fib(n - 2, depth + 4);
    printf("%-*c fib(%d) = %d\n", depth, '>', n, res);
    return res;
}

int main() {
    int n;
    scanf("%d", &n); // считываем число n с клавиатуры (например, "20
    printf("main: fib(%d) = %d\n", n, fib(n, 1));
    
    // Выводим общее количество вызовов функции fib
    printf("Всего выполнено %d вызовов функции fib.\n", call_count);
    
    return 0;
}