#include <stdio.h>

// Проверяет, является ли символ допустимым для чередующейся последовательности
int is_ah(char c) {
    return c == 'a' || c == 'h';
}

// Находит длину чередующейся подстроки a/h, начиная с start
int find_alternating_length(const char* s, int start) {
    if (!is_ah(s[start])) return 0;

    char prev = s[start];
    int has_a = (prev == 'a');
    int len = 1;

    for (int i = start + 1; s[i] != '\0'; i++) {
        if (!is_ah(s[i]) || s[i] == prev) break;
        prev = s[i];
        len++;
        if (s[i] == 'a') has_a = 1;
    }

    return has_a ? len : 0;
}

// Находит длину подстроки из одних 'a', начиная с start
int find_aaa_length(const char* s, int start) {
    if (s[start] != 'a') return 0;
    int len = 0;
    while (s[start + len] == 'a') {
        len++;
    }
    return len;  // длина >=1, и содержит 'a' — всегда подходит
}

int main() {
    int n;
    scanf("%d", &n);

    char s[100000];
    scanf("%s", s);

    int max_len = 0;

    // Проверяем все позиции
    for (int j = 0; s[j] != '\0'; j++) {
        int alt_len = find_alternating_length(s, j);
        int aaa_len = find_aaa_length(s, j);
        
        int current_len = (alt_len > aaa_len) ? alt_len : aaa_len;
        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    printf("%d\n", max_len);
    return 0;
}