#include "grep_3.h"

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s [OPTIONS] PATTERN [FILE...]\n", prog_name);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -i        Ignore case\n");
    fprintf(stderr, "  -v        Invert match\n");
    fprintf(stderr, "  -c        Count matches\n");
    fprintf(stderr, "  -n        Show line numbers\n");
    fprintf(stderr, "  -l        Show file names with matches\n");
    fprintf(stderr, "  -L        Show file names without matches\n");
    fprintf(stderr, "  -h        Suppress file names in output\n");
    fprintf(stderr, "  -H        Display file names in output\n");
    fprintf(stderr, "  -q        Quiet, return only exit status\n");
    fprintf(stderr, "  -e PATTERN Specify a pattern\n");
    fprintf(stderr, "  -s        Suppress error messages\n");
    fprintf(stderr, "  -f FILE   Read patterns from FILE\n");
    fprintf(stderr, "  -o        Print only matched parts\n");
    // Можно добавлять опции по мере необходимости
}

int grep_file(const char *filename, const char *pattern, int flags, int file_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        // Подавлять сообщения об ошибках с помощью -s
        if (errno == ENOENT && !(flags & 256)) {
            fprintf(stderr, "%s: No such file or directory\n", filename);
        } else {
            perror("fopen");
        }
        return -1;
    }

    const char *error = NULL;
    size_t erroffset;
    int errorcode;
    int pcre_flags = 0;
    if (flags & 1) { // Игнорировать регистр
        pcre_flags |= PCRE2_CASELESS;
    }

    pcre2_code *re = pcre2_compile((PCRE2_SPTR)pattern, PCRE2_ZERO_TERMINATED, pcre_flags, &errorcode, &erroffset, NULL);
    if (!re) {
        // Подавлять сообщения об ошибках с помощью -s
        if (!(flags & 256)) {
            fprintf(stderr, "PCRE2 compilation failed at offset %ld: %s\n", erroffset, error);
        }
        fclose(file);
        return -1;
    }

    // Создание соответствующих данных
    pcre2_match_data *match_data = pcre2_match_data_create(30, NULL);
    if (!match_data) {
        fprintf(stderr, "Failed to create match data\n");
        pcre2_code_free(re);
        fclose(file);
        return -1;
    }

    char line[1024];
    int line_number = 0;
    int match_count = 0;
    int match_found = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        int ret = pcre2_match(re, (PCRE2_SPTR)line, strlen(line), 0, 0, match_data, NULL);
        int is_match = (ret >= 0);

        if (flags & 2) { // Инвертировать совпадение
            is_match = !is_match;
        }

        if (is_match) {
            match_found = 1;
            match_count++;
            if (flags & 16) { // Тихий режим
                break;
            }

            if ((file_count > 1 && !(flags & 64)) || (flags & 128 && match_found)) {
                printf("%s:", filename);
            }
            
            if (flags & 128 && match_found) {
                // Имя файла с совпаднием
                printf("%s\n", filename);
                break;
            }
            if (flags & 32) { // Имя файла без совпадения
                // Ничего не делать, если совпадение найдено
                break;
            }
            if (flags & 8) { // Подсчет совпадений
                continue;
            }
            if (flags & 4) { // Номер строки
                printf("%s:%d:", filename, line_number);
            }
            if (!(flags & 64)) {
                printf("%s:", filename);
            }
            if (flags & 128 || flags & 32) {
                printf("%s\n", filename);
            }
            if (flags & 512) { // Только совпадения -о
                // Предполагается, что данные о совпадениях действительны и содержат совпадения
                size_t *ptr = pcre2_get_ovector_pointer(match_data);
                for (int i = 0; i < ret; i++) {
                    size_t start = ptr[2 * i];
                    size_t end = ptr[2 * i + 1];
                    fwrite(line + start, sizeof(char), end - start, stdout);
                    printf("\n");
                }
            } else {
                printf("%s", line);
            }
        }
    }

    if (flags & 8) { // Подсчет совпадений
        printf("%s:%d", filename, match_count);
    }

    if (flags & 32) { // Имя файла без совпадения
        if (!match_found) {
            printf("%s", filename);
        }
    }

    if (feof(file) && !(flags & 4) && !(flags & 64) && (flags & 64)) {
        putchar('\n');
    }

    fclose(file);
    pcre2_match_data_free(match_data); // Освободить память затую структурой match data
    pcre2_code_free(re); // Освободить скомпилированное регулярное выражение

    return match_found ? 0 : 1;
}

int main(int argc, char **argv) {
    int opt;
    int flags = 0;
    char *pattern[100];
    int pattern_count = 0;
    int file_count = 0;

    while ((opt = getopt(argc, argv, "ivcnlhHLqse:f:o")) != -1) {
        switch (opt) {
            case 'i':
                flags |= 1;
                break;
            case 'v':
                flags |= 2;
                break;
            case 'c':
                flags |= 8;
                break;
            case 'n':
                flags |= 4;
                break;
            case 'l':
                flags |= 128;
                break;
            case 'L':
                flags |= 32;
                break;
            case 'h':
                flags |= 64;
                break;
            case 'H':
                flags &= ~64;
                break;
            case 'q':
                flags |= 16;
                break;
            case 'e':
                pattern[pattern_count++] = optarg; // Сохранить шаблон
                break;
            case 's':
                flags |= 256; // Подавить сообщения об ошибках
                break;
            case 'f':
                FILE *pattern_file = fopen(optarg, "r");
                if (!pattern_file) {
                    fprintf(stderr, "Failed to open pattern file '%s': %s\n", optarg, strerror(errno));
                    perror("fopen");
                    exit(EXIT_FAILURE);
                    }
                    
                char file_pattern[1024];
                // Сохраните все файлы для обработки
                int file_count = argc - optind; // Количество файлов в командной строке
                char **files = &argv[optind]; // Указатель на массив файлов

                // Чтение шаблонов из файла
                while (fgets(file_pattern, sizeof(file_pattern), pattern_file)) {
                    file_pattern[strcspn(file_pattern, "\n")] = 0; // Убирает символ новой строки
                    // Обработка каждого файла с текущим шаблоном
                    for (int i = optind; i < argc; i++) {
                        grep_file(files[i], pattern[0], flags, file_count);
                    }
                }
                fclose(pattern_file);
                break;
            
            case 'o':
                flags |= 512; // Только части совпадений
                break;
            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (pattern_count == 0 && optind >= argc) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pattern_count == 0) {
        pattern[pattern_count++] = argv[optind]; // Если нет флага -e, взять из аргументов
    }

    //if (pattern_count != 0 && EOF) {
    //printf("\n");
    //}

    if (optind >= argc) {
        fprintf(stderr, "No pattern provided.\n");
        return 1; // Завершение с ошибкой
    }

    for (int i = 0; i < pattern_count; i++) {
        if (optind == argc - 1) {
        // Чтение из стандартного ввода
            if (grep_file(argv[optind], pattern[i], flags, file_count) == -1) {
                fprintf(stderr, "Error processing standard input.\n");
            } else {
                for (int j = optind + 1; j < argc; j++) {
                    if (grep_file(argv[j], pattern[i], flags, file_count) == -1) {
                        fprintf(stderr, "Error processing file: %s\n", argv[j]);
                    }
                }
            }
        }
    }

    return 0;
}