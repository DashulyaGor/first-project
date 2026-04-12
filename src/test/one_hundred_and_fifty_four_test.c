#include <stdio.h>
#include <string.h>

#define MAX 1000

int main(){
    char line[MAX];
    int found = 0;  // флаг: найдено ли слово "bomb"

    const char *delim = " \t\n\r.,!?:;\"()-[]{}<>";

    // Читаем строки, пока не EOF или пустая строка
    while (fgets(line, sizeof(line), stdin) != NULL) {
        // Убираем символ новой строки, если есть
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        // Если строка пустая — завершаем ввод
        if (len == 0) {
            break;
        }

        // Разбиваем строку на слова
        char *token = strtok(line, delim);
        while (token != NULL) {
            // Сравниваем слово точно с "bomb"
            if (strcmp(token, "bomb") == 0) {
                found = 1;  // нашли точное совпадение
                break;      // можно выйти из обработки этой строки
            }
            token = strtok(NULL, delim);
        }
    }

    // Выводим результат
    printf(found ? "YES\n" : "NO\n");

    return 0;
}