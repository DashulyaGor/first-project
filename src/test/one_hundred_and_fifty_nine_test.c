#include <stdio.h>
#include <string.h>

// Проверка, является ли строка палиндромом
int is_palindrome(const char *s, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

// Проверка, состоит ли строка из повторений блока s[0..len-1]
int is_repeated(const char *s, int n, int len) {
    for (int i = 0; i < n; i++) {
        if (s[i] != s[i % len]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char s[101];
    scanf("%100s", s);  // читаем строку до 100 символов

    int n = strlen(s);

    // Строка из одного символа — всегда украшение
    if (n == 1) {
        printf("%c\n", s[0]);
        return 0;
    }

    // Перебираем все возможные длины периода
    for (int len = 1; len < n; len++) {
        if (n % len != 0) continue;  // должно делиться нацело

        // Блок s[0..len-1]
        if (!is_palindrome(s, len)) continue;

        // Проверяем, повторяется ли блок
        if (is_repeated(s, n, len)) {
            // Выводим минимальный период и выходим
            for (int i = 0; i < len; i++) {
                printf("%c", s[i]);
            }
            printf("\n");
            return 0;
        }
    }

    // Ни один период не подошёл
    printf("NO\n");
    return 0;
}