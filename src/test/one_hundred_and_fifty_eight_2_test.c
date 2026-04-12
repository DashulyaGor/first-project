#include <stdio.h>
#include <string.h>


void replace(char * src);

int main()
{
    char d[2000] = {0};

    // Чтение всей строки с пробелами
    while(fgets(d, sizeof(d), stdin) != NULL) {
        // Удаление символа '\n', если он есть
        size_t len = strlen(d);
        if (len > 0 && d[len - 1] == '\n') {
            d[len - 1] = '\0';
            len = strlen(d);
        }

        if (len == 0) {
            break;
        }
    }
    replace(d);

    printf("%s\n", d);
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