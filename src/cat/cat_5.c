#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

void print_file(FILE *file, int flags);

int main(int argc, char **argv) {
    int number_lines = 0;
    int number_nonblank = 0;
    int squeeze_blank = 0;
    int show_ends = 0;
    int show_tabs = 0;
    int show_nonprinting = 0;
    int all = 0;
    int e_flag = 0;
    int t_flag = 0;

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

    int flags = number_lines | (number_nonblank << 1) | (squeeze_blank << 2) | (show_ends << 3) | (show_tabs << 4) | (show_nonprinting << 5);

    if (argc == 1 || (argc == 2 && !strcmp(argv[1], "-"))) {
        print_file(stdin, flags);
    } else {
        for (int i = 2; i < argc; ++i) {
            if (argv[i][0] == '-') continue;
            FILE *file = fopen(argv[i], "r");
            if (file != NULL) {
                print_file(file, flags);
                fclose(file);
            } else {
                fprintf(stderr, "File opening error: %s\n", argv[i]);
                perror("Something went wrong!");
            }
        }
    }

    return 0;
}

void print_file(FILE *file, int flags) {
    char line[MAX_LINE_LENGTH];
    int line_number = 1;
    int prev_was_empty = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if ((flags & (1 << 2)) && prev_was_empty && strlen(line) == 0) {
            continue;
        }

        if (flags & (1 << 1)) {
            if (strlen(line) > 0) {
                printf("%6d\t", line_number++);
            }
        } else if (flags & 1) {
            printf("%6d\t", line_number++);
        }

        for (char *p = line; *p; p++) {
            if ((flags & (1 << 4)) && *p == '\t') {
                printf("^I");
            } else if ((flags & (1 << 5)) && (*p < ' ' || *p > '~')) {
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
            } else {
                putchar(*p);
            }
        }

        if (flags & (1 << 3)) {
            printf("$");
        }

        putchar('\n');
        prev_was_empty = (strlen(line) == 0);
    }
}