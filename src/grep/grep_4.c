#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#define pcre2_compile PCRE2_SUFFIX(pcre2_compile_)
#define pcre2_code PCRE2_SUFFIX(pcre2_code_)
#define pcre2_get_ovector_pointer PCRE2_SUFFIX(pcre2_get_ovector_pointer_)

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
}

int grep_file(const char *filename, const char *pattern, int flags) {
    FILE *file = fopen(filename, "r");
    if (!file) {
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

    pcre2_code *re = pcre2_compile((PCRE2_SPTR) pattern, PCRE2_ZERO_TERMINATED, pcre_flags, &errorcode, &erroffset, NULL);
    if (!re) {
        if (!(flags & 256)) { 
            fprintf(stderr, "PCRE2 compilation failed at offset %ld: %s\n", erroffset, error);
        }
        fclose(file);
        return -1;
    }

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

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        int ret = pcre2_match(re, (PCRE2_SPTR)line, strlen(line), 0, 0, match_data, NULL);
        if (flags & 2) { // Invert match
            if (ret >= 0) {
                continue; // Если совпадение, пропускаем вывод
            }
        } else if (ret >= 0) {
            match_count++;
            if (!(flags & 64)) { // Если не подавляем имена файлов
                printf("%s:", filename);
            }
            if (flags & 8) { // Если требуется показать номера строк
                printf("%d:", line_number);
            }
            printf("%s", line); // Вывод строки
        }
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
    fclose(file);
    return match_count;
}

int main(int argc, char *argv[]) {
    int flags = 0;
    char *pattern = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "ivcnlLhHqes:f:o")) != -1) {
        switch (opt) {
            case 'i':
                flags |= 1; // Ignore case
                break;
            case 'v':
                flags |= 2; // Invert match
                break;
            case 'c':
                flags |= 4; // Count matches
                break;
            case 'n':
                flags |= 8; // Show line numbers
                break;
            case 'l':
                flags |= 16; // Show file names with matches
                break;
            case 'L':
                flags |= 32; // Show file names without matches
                break;
            case 'h':
                flags |= 64; // Suppress file names
                break;
            case 'H':
                flags |= 128; // Display file names
                break;
            case 'q':
                flags |= 256; // Quiet mode
                break;
            case 'e':
                pattern = optarg; // Store the pattern
                break;
            case 's':
                flags |= 512; // Suppress error messages
                break;
            case 'f':
                // Logic for reading patterns from file would go here
                break;
            case 'o':
                flags |= 1024; // Print only matched parts
                break;
            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!pattern) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Process the files
    for (int i = optind; i < argc; i++) {
        grep_file(argv[i], pattern, flags);
    }

    return 0;
}