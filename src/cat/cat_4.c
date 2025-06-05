#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

void print_file(FILE *file, int flags);

int main(int argc, char **argv) {
    // Флаг -n (нумерация строк)
    int number_lines = 0;
    
    // Флаг -b (нумерация непустых строк)
    int number_nonblank = 0;
    
    // Флаг -s (удаление повторяющихся пустых строк)
    int squeeze_blank = 0;
    
    // Флаг -E (добавление символа $ к концу каждой строки)
    int show_ends = 0;
    
    // Флаг -T (замена табуляций на ^I)
    int show_tabs = 0;
    
    // Флаг -v (вывод невидимых символов)
    int show_nonprinting = 0;
    
    // Флаг -A (включает -vET)
    int all = 0;
    
    // Флаг -e (эквивалентен -vE)
    int e_flag = 0;
    
    // Флаг -t (эквивалентен -vT)
    int t_flag = 0;
    
    // Парсим аргументы командной строки
    for (int i = 1; i < argc; ++i) {
    if (!strcmp(argv[i], "-n")) {
        number_lines = 1;
    } else if (!strcmp(argv[i], "-b")) {
        number_nonblank = 1;
    } else if (!strcmp(argv[i], "-s")) {
        squeeze_blank = 1;
    } else if (!strcmp(argv[i], "-E")) {
        show_ends = 1;
    } else if (!strcmp(argv[i], "-T")) {
        show_tabs = 1;
    } else if (!strcmp(argv[i], "-v")) {
        show_nonprinting = 1;
    } else if (!strcmp(argv[i], "-A")) {
        all = 1;
    } else if (!strcmp(argv[i], "-e")) {
        e_flag = 1;
    } else if (!strcmp(argv[i], "-t")) {
        t_flag = 1;
    }
    }
    
    // Обрабатываем флаги -A, -e, -t
    if (all) {
    show_nonprinting = 1;
    show_ends = 1;
    show_tabs = 1;
    }
    
    if (e_flag) {
    show_nonprinting = 1;
    show_ends = 1;
    }
    if (t_flag) {
    show_nonprinting = 1;
    show_tabs = 1;
    }
    
    // Если файлы не указаны, читаем из стандартного ввода
    if (argc == 1 || !strcmp(argv[1], "-")) {
    print_file(stdin, number_lines | number_nonblank << 1 | squeeze_blank << 2 | show_ends << 3 | show_tabs << 4 | show_nonprinting << 5);
    } else {
        for (int i = 1; i < argc; ++i) {
        FILE *file = fopen(argv[i], "r");
        if (file != NULL) {
            print_file(file, number_lines | number_nonblank << 1 | squeeze_blank << 2 | show_ends << 3 | show_tabs << 4 | show_nonprinting << 5);
            fclose(file);
        } else {
            perror("Something went wrong!");
        }
    }
}

return 0;
}

// Функция для печати содержимого файла с учетом всех возможных флагов
void print_file(FILE *file, int flags) {
    char line[MAX_LINE_LENGTH];
    int line_number = 1;
    int prev_was_empty = 0;


while (fgets(line, sizeof(line), file)) {
    // Удаляем символ новой строки в конце строки
    line[strcspn(line, "\n")] = '\0';
    
    // Проверка флага -s (squeeze_blank)
    if ((flags & (1 << 2)) && prev_was_empty && strlen(line) == 0) {
        continue;
    }
    
    // Проверка флага -b (number_nonblank)
    if ((flags & (1 << 1)) && strlen(line) > 0) {
        printf("%6d\t%s\n", line_number++, line);
    } else if ((flags & 1) && !(flags & (1 << 1))) { // Флаг -n (number_lines)
        printf("%6d\t%s\n", line_number++, line);
    } else {
        printf("%s\n", line);
    }
    
    // Проверка флага -E (show_ends)
    if (flags & (1 << 3)) {
        printf("$");
    }
    
    // Проверка флага -T (show_tabs)
    if (flags & (1 << 4)) {
        for (char *p = line; *p; p++) {
            if (*p == '\t') {
                putchar('^');
                putchar('I');
            } else {
                putchar(*p);
            }
        }
    }
    
    // Проверка флага -v (show_nonprinting)
    if (flags & (1 << 5)) {
        for (char *p = line; *p; p++) {
            if (*p >= ' ' && *p <= '~') {
                putchar(*p);
                } else {
                    switch (*p) {
                        case '\t':
                            printf("^I");
                        break;
                        case '\n':
                            printf("^J");
                        break;
                        case '\r':
                            printf("^M");
                        break;
                        default:
                            printf("^%c", *p + '@');
                        break;
                        }
                    }
                }
            }
        }

                if (flags & (3 << 5)) {
            putchar('\n');
    }
    
        // Установка флага prev_was_empty
        prev_was_empty = (strlen(line) == 0);
}