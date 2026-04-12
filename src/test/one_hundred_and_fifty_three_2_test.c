#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

int main() {
    char word[MAX_LEN + 1];
    char longest_word[MAX_LEN + 1] = "";
    int max_length = 0;

    // Читаем каждое слово через scanf
    while (scanf("%1000s", word) == 1) {
        if (strcmp(word, "END") == 0 || strcmp(word, "end") == 0) {
            break;
        }
        int len = strlen(word);

        // Обновляем только если строго длиннее
        if (len > max_length) {
            strcpy(longest_word, word);
            max_length = len;
        }
    }

    // Вывод результата
    if (max_length > 0) {
        printf("%s %d\n", longest_word, max_length);
    } else {
        printf("0\n");
    }

    return 0;
}