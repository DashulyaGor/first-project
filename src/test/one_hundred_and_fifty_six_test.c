#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX 1000

char * stringtolower(char * s) {
    for (int i = 0; s[i]; i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}

int main() {
    char line[MAX];
    const char *substr = "bomb";
    int found = 0;  // флаг: найдено ли слово "bomb"

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
        // Проверяем, есть ли "bomb" в текущей строке
        if (strstr(stringtolower(line), substr) != NULL) {
            found = 1; // помечаем, что нашли
        }
    }

    // Выводим ОДИН результат после обработки всех строк
    if (found) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}