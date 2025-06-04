#include <stdio.h>

// Функция вывода множителя
void printFactor(unsigned int last, unsigned int n) {
    if (n == 1) {
        printf("%u ", last);
    } else if (n > 1) {
        printf("%u^%u ", last, n);
    }
}

// Основная рекурсивная функция для нахождения простых множителей
void simpleFactors(unsigned int a, unsigned int last, unsigned int n) {
    printf("meaning of simpleFactors(%u, %u, %u)\n", a, last, n);
    if (a == 1) {
        if (n > 0) {
            printFactor(last, n);
        }
        return;
    }

    // Деление на текущий делитель
    if (a % last == 0) {
        simpleFactors(a / last, last, n + 1);
    } else {
        // Печатаем предыдущий найденный множитель, если он был
        if (n > 0) {
            printFactor(last, n);
        }
        
        // Переход к следующему возможному простому делителю
        if (last == 2) {
            simpleFactors(a, 3, 0); // Первый раз пропускаем все четные числа
        } else {
            simpleFactors(a, last + 2, 0); // Далее проходим только нечётные числа
        }
    }
}

int main() {
    unsigned int num; // Число для проверки
    scanf("%u", &num);
    simpleFactors(num, 2, 0); // Начинаем разложение с первого простого числа (2)
    printf("\n");
    return 0;
}