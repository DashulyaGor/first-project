#include <stdio.h>
#include <string.h>

#define MAX 10000

int main() {
    int num, den;
    scanf("%d %d", &num, &den);

    // Результат: целая часть (всегда 0, т.к. дробь правильная), непериодическая и периодическая части
    char result[MAX] = "0";
    int remainder = num;
    int index = 1;  // Начинаем заполнение после '0'
    int remainder_index[MAX] = {0};  // Для хранения позиции каждого остатка

    // Записываем запятую
    result[index++] = ',';

    // Пока остаток не станет 0 или не найдём повтор
    while (remainder != 0 && remainder_index[remainder] == 0) {
        remainder_index[remainder] = index;
        remainder *= 10;
        int digit = remainder / den;
        result[index++] = digit + '0';
        remainder = remainder % den;
    }

    // Обработка результата
    if (remainder == 0) {
        // Дробь конечная
        result[index] = '(';
        result[index + 1] = '0';
        result[index + 2] = ')';
        result[index + 3] = '\0';
    } else {
        // Дробь периодическая
        int start = remainder_index[remainder] - 1;  // Индекс начала периода
        memmove(result + start + 1 + 1, result + start + 1, index - start);
        result[start + 1] = '(';
        result[index + 1] = ')';
        result[index + 2] = '\0';
    }

    printf("%s\n", result);

    return 0;
}
