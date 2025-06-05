#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

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
    // Можно добавлять опции по мере необходимости
}

int grep_file(const char *filename, const char *pattern, int flags) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        // Подавлять сообщения об ошибках с помощью -s
        if (!(flags & 256)) { 
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
    int printed_filename = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        int ret = pcre2_match(re, (PCRE2_SPTR)line, strlen(line), 0, 0, match_data, NULL);
        int is_match = (ret >= 0);

        if (flags & 2) { // Invert match
            is_match = !is_match;
        }

        if (is_match) {
            match_found = 1;
            match_count++;
            if (flags & 16) { // Quiet mode
                break;
            }
            if (flags & 128 && match_found && !printed_filename) {
                printed_filename = 1; // File name with match
                printf("%s\n", filename);
            }
            if (flags & 32) { // File name without match
                // Do nothing if match is found
                break;
            }
            if (flags & 8) { // Count matches
                continue;
            }
            if (flags & 4) { // Line number
                printf("%d:", line_number);
            }
            if (!(flags & 64)) { // Suppress file name
                printf("%s:", filename);
            }
             if (flags & 512) { // Only matches
                // Assuming match data is valid and contains matches
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

    fclose(file);
    pcre2_match_data_free(match_data); // Free the match data
    pcre2_code_free(re); // Free the compiled regex

    if (flags & 8) { // Count matches
        printf("%d\n", match_count);
    }

    if (flags & 32) { // File name without match
        if (!match_found) {
            printf("%s\n", filename);
        }
    } //else if (flags & 128 && match_found) { // File name with match
            //printf("%s\n", filename);
            //}

    return match_found ? 0 : 1;
}

int main(int argc, char **argv) {
    int opt;
    int flags = 0;
    char *pattern = NULL;

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
                pattern = optarg; // Store the pattern
                break;
            case 's':
                flags |= 256; // Suppress error messages
                break;
            case 'f': {
                FILE *pattern_file = fopen(optarg, "r");
                if (!pattern_file) {
                    perror("fopen");
                    exit(EXIT_FAILURE);
                }
                char file_pattern[1024];
                while (fgets(file_pattern, sizeof(file_pattern), pattern_file)) {
                    file_pattern[strcspn(file_pattern, "\n")] = 0; // Remove newline
                    grep_file("-", file_pattern, flags); // Use stdin for pattern
                }
                fclose(pattern_file);
                break;
            }
            case 'o':
                flags |= 512; // Only matched parts
                break;
            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!pattern && optind >= argc) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!pattern) {
        pattern = argv[optind]; // If no -e flag, take from arguments
    }

    //const char *pattern = argv[optind];

    if (optind == argc - 1) {
        // Read from stdin
        grep_file("-", pattern, flags);
    } else {
        for (int i = optind + 1; i < argc; i++) {
            if (grep_file(argv[i], pattern, flags) == -1) {
                fprintf(stderr, "Error processing file: %s\n", argv[i]);
            }
        }
    }
    return 0;
}