#include <stdio.h>
#include <ctype.h>

int number_lines(int argc, char *argv[]) {
    int number_lines = 0;

    // Чтение файла построчно и увеличение счетчика
    FILE *file = fopen("example.txt", "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            number_lines++;
        }
        fclose(file);
    }

    printf("Количество строк в файле: %d\n", number_lines);
    return 0;
}

int number_nonblank(int argc, char *argv[]) {
    int number_nonblank = 0;

    // Чтение файла построчно и увеличение счетчика для непустых строк
    FILE *file = fopen("example.txt", "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            // Проверяем, есть ли в строке символы, отличные от пробельных
            int is_nonblank = 0;
            for (int i = 0; buffer[i]; i++) {
                if (!isspace((unsigned char)buffer[i])) {
                    is_nonblank = 1;
                    break;
                }
            }
            if (is_nonblank) {
                number_nonblank++;
            }
        }
        fclose(file);
    }

    printf("Количество непустых строк в файле: %d\n", number_nonblank);
    return 0;
}

int squeeze_blank(int argc, char *argv[]) {
    int previous_line_was_empty = 0;

    // Чтение файла построчно и удаление нескольких подряд идущих пустых строк
    FILE *file = fopen("example.txt", "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            // Проверяем, является ли текущая строка пустой
            int current_line_is_empty = 1;
            for (int i = 0; buffer[i]; i++) {
                if (!isspace((unsigned char)buffer[i])) {
                    current_line_is_empty = 0;
                    break;
                }
            }

            // Печатаем строку, если она не пустая или если предыдущее условие было нарушено
            if (!current_line_is_empty || !previous_line_was_empty) {
                fputs(buffer, stdout);
            }

            // Обновляем состояние предыдущей строки
            previous_line_was_empty = current_line_is_empty;
        }
        fclose(file);
    }

    return 0;
}


int show_ends(int argc, char *argv[]) {
    int show_ends = 1;

    // Чтение файла построчно и добавление символа '$' в конец каждой строки
    FILE *file = fopen("example.txt", "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            // Выводим строку без символа новой строки
            printf("%.*s", (int)strlen(buffer) - 1, buffer);

            // Добавляем символ '$', если установлен соответствующий флаг
            if (show_ends) {
                printf("$");
            }

            // Переходим на новую строку
            printf("\n");
        }
        fclose(file);
    }

    return 0;
}

int show_tabs(int argc, char *argv[]) {
    int show_tabs = 1;

    // Чтение файла построчно и замена табуляций на ^I
    FILE *file = fopen("example.txt", "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            for (int i = 0; buffer[i]; i++) {
                if (buffer[i] == '\t' && show_tabs) {
                    printf("^I");
                } else {
                    putchar(buffer[i]);
                }
            }
            printf("\n");
        }
        fclose(file);
    }

    return 0;
}


int show_nonprinting(int argc, char *argv[]) {
    int show_nonprinting = 1;

    // Чтение файла построчно и замена невидимых символов на видимые эквиваленты
    FILE *file = fopen("example.txt", "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            for (int i = 0; buffer[i]; i++) {
                if (buffer[i] == '\t' && show_nonprinting) {
                    printf("^I");
                } else if (buffer[i] == '\n' && show_nonprinting) {
                    printf("$");
                } else if (buffer[i] == '\r' && show_nonprinting) {
                    printf("^M");
                } else if (buffer[i] == '\x07' && show_nonprinting) {
                    printf("^G");
                } else {
                    putchar(buffer[i]);
                }
            }
            printf("\n");
        }
        fclose(file);
    }

    return 0;
}


int all(int argc, char *argv[]) {
    int all = 0;

    // Чтение файла построчно и замена табуляций на ^I
    FILE *file = fopen("example.txt", "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            for (int i = 0; buffer[i]; i++) {
                if (buffer[i] == '\t' && all) {
                    printf("^I");
                } else {
                    putchar(buffer[i]);
                }
            }
            printf("\n");
        }
        fclose(file);
    }

    return 0;
}


int e_flag(int argc, char *argv[]) {
    int e_flag = 1;

    // Чтение файла построчно и замена конца строки на $
    FILE *file = fopen("example.txt", "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            // Выводим строку без символа новой строки
            printf("%.*s", (int)strlen(buffer) - 1, buffer);

            // Добавляем символ $ в конец каждой строки
            if (e_flag) {
                printf("$");
            }

            // Переходим на новую строку
            printf("\n");
        }
        fclose(file);
    }

    return 0;
}


int t_flag(int argc, char *argv[]) {
    int t_flag = 1;

    // Чтение файла построчно и замена табуляций на ^I
    FILE *file = fopen("example.txt", "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            for (int i = 0; buffer[i]; i++) {
                if (buffer[i] == '\t' && t_flag) {
                    printf("^I");
                } else {
                    putchar(buffer[i]);
                }
            }
            printf("\n");
        }
        fclose(file);
    }

    return 0;
}