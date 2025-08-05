#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int d;
    char k_str[1000]; // Массив для хранения большого числа в виде строки
    int count = 0;

    // Ввод данных
    scanf("%d", &d);
    scanf("%s", k_str);

    // Сохраняем оригинальное значение числа
    char original_k_str[1000];
    strcpy(original_k_str, k_str);

    // Проверка корректности ввода (только цифры)
    for (int i = 0; k_str[i] != '\0'; ++i) {
        if (!isdigit(k_str[i])) {
            printf("Ошибка: ввод содержит недопустимые символы.\n");
            return 1;
        }
    }

    // Подсчёт повторений цифры d
    for (int i = 0; k_str[i] != '\0'; ++i) {
        if (k_str[i] == '0' + d) { // Преобразуем d в символ
            count++;
        }
    }

    // Вывод результата
    printf("%d %s %d\n", d, original_k_str, count);
    return 0;
}