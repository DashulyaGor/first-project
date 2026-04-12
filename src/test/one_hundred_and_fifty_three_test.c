#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

int main() {
    char line[MAX_LEN + 1];
    
    // Буфер для хранения самого длинного слова
    char longest_word[1000] = "";
    int max_length = 0;

    // Разделители слов
    const char *delim = " \t\n\r ,.!?:;\"()-[]{}<>";

    // Читаем ВСЕ строки, пока не EOF
    while (fgets(line, sizeof(line), stdin) != NULL) {
        // Убираем '\n', если есть
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        if (len == 0) {
            break;  // пустая строка — конец ввода
        }

        // Разбиваем текущую строку на слова
        char *token = strtok(line, delim);
        while (token != NULL) {
            int current_length = strlen(token);

            // Обновляем, только если строго длиннее
            if (current_length > max_length) {
                strcpy(longest_word, token);
                max_length = current_length;
            }

            token = strtok(NULL, delim);
        }
    }

    // Вывод результата
    if (max_length > 0) {
        printf("%s %d\n", longest_word, max_length);
    } else {
        printf("\n0\n");
    }

    return 0;
}