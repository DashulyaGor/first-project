#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Проверяет, является ли символ допустимым
int is_ah(char c) {
    c = tolower(c);
    return c == 'a' || c == 'h';
}

// Находит длину чередующейся подстроки
int find_alternating_length(const char* s, int start) {
    if (!is_ah(s[start])) return 0;

    char prev = tolower(s[start]);
    int has_a = (prev == 'a');
    int len = 1;

    for (int i = start + 1; s[i] != '\0'; i++) {
        char curr = tolower(s[i]);
        if (!is_ah(s[i]) || curr == prev) break;
        prev = curr;
        len++;
        if (curr == 'a') has_a = 1;
    }

    return has_a ? len : 0;
}

int main() {
    int n;
    scanf("%d", &n);

    char s[100000];
    scanf("%99999s", s);
    if ((int)strlen(s) > n) return 1;  // Проверка на переполнение

    int max_len = 0;

    // Попробуем начать последовательность с каждой позиции
    for (int j = 0; s[j] != '\0'; j++) {
        int current_len = find_alternating_length(s, j);
        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    printf("%d\n", max_len);

    return 0;
}