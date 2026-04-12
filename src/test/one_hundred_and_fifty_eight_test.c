#include <stdio.h>
#include <string.h>


void replace(char * src);

int main() {
    char full_text[2000] = {0};  // весь текст
    char line[2000];
    size_t total_len = 0;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        if (len == 0) break;

        // Добавляем строку в full_text
        if (total_len + len + 2 < 2000) {
            strcat(full_text, line);
            strcat(full_text, "\n");
            total_len = strlen(full_text);
        }
    }

    replace(full_text);
    printf("%s", full_text);  // уже с \n внутри

    return 0;
}


void replace(char * src)
{
    const char *find = "bomb";
    const char *replace_with = "watermelon";

    size_t len_find = strlen(find);        // 4
    size_t len_replace = strlen(replace_with); // 10

    char *p = src;

    while ((p = strstr(p, find)) != NULL) {  // ищем следующее вхождение
        size_t tail_len = strlen(p + len_find) + 1;  // длина хвоста + \0

        // Проверяем, хватит ли места
        if (p - src + len_replace + tail_len >= 2000) {
            break;  // недостаточно места — прерываем
        }

        // Сдвигаем хвост вправо
        memmove(p + len_replace, p + len_find, tail_len);

        // Вставляем "watermelon"
        memcpy(p, replace_with, len_replace);

        // Перемещаем указатель за вставленную строку
        p += len_replace;
    }
}