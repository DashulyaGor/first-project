#include <stdio.h>
#include <string.h>

int main() {
    char s[10];      // буфер для слова (достаточно: "Treasure!" — 9 символов)
    int steps;
    int x = 0, y = 0; // начальные координаты

    while (1) {
        scanf("%9s", s); // читаем слово (не более 9 символов)

        // Проверяем, не конец ли ввода?
        if (strcmp(s, "Treasure!") == 0) {
            break; // выход из цикла
        }

        // Читаем количество шагов
        scanf("%d", &steps);

        // Обрабатываем направление
        if (strcmp(s, "North") == 0) {
            y += steps;
        } else if (strcmp(s, "South") == 0) {
            y -= steps;
        } else if (strcmp(s, "East") == 0) {
            x += steps;
        } else if (strcmp(s, "West") == 0) {
            x -= steps;
        }
    }

    printf("%d %d\n", x, y);
    return 0;
}