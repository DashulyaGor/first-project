#include "s21_cat.h"

//int getopt_long(int argc, char *argv[],
//    const char *optstring,
//    const struct option *longopts, int *longindex);


Flags CatReadFlags(int argc, char *argv[]) {
    struct option long_options[] = {
        {"number_nonblanck", 0, NULL, 'b'},
        {"number_lines", 0, NULL, 'n'},
        {"squeeze_blanck", 0, NULL, 's'},
        {NULL, 0, NULL, 0}
    };
    int current_flag = getopt_long(argc, argv, "benstEvT", long_options, NULL);
Flags flags = {false, false, false, false, false, false};
    for (;current_flag != -1; current_flag = getopt_long(argc, argv, "benstEvT", long_options, NULL)) {
        switch(current_flag) {
            case 'b':
            flags.number_nonblanck = true;
            break; case 'e':
            flags.show_nonprinting = true;
            flags.show_ends = true;
            break; case 'v':
            flags.show_nonprinting = true;
            break; case 'E':
            flags.show_ends = true;
            break; case 'n':
            flags.number_lines = true;
            break; case 's':
            flags.squeeze_blanck = true;
            break; case 't':
            flags.show_tabs = true;
            break; case 'T':
            flags.show_tabs = true;
            flags.show_nonprinting = true;
            break;
        }
    }
    return flags;
}

void CatFile(FILE *file, Flags flags, const char *table[static 256]) {
    int c = 0;
    int last = '\n';
    (void)flags;
    int line = 0;

    while(fread(&c, 1, 1, file) > 0) {
        if (last == '\n') {
            if (flags.squeeze_blanck && c == '\n')
                continue;
            if (flags.number_lines) {
                printf("%6i  ", ++line);
            }
            else if (flags.number_nonblanck) {
                if (c != '\n')
                    printf("%6i  ", ++line);
            }
        }
        if (!*table[c])
            printf("\\0");
        else
            printf("%s", table[c]);
        last = c;
    }
}

void Cat(int argc, char *argv[], Flags flags, const char *table[static 256]) {
    for (char **filename = &argv[1], **end = &argv[argc]; filename != end; ++filename) {
        if (**filename == '-')
            continue;
        FILE *file = fopen(*filename, "rb");
        if (errno) {
            fprintf(stderr, "%s", argv[0]);
            perror(*filename);
            continue;
        }
        CatFile(file, flags, table);
        fclose(file);
    }
}

int main(int argc, char *argv[]) {
    Flags flags = CatReadFlags(argc, argv);
    const char *table[256];
    if (flags.show_ends)
        CatSetEnds(table);
    if (flags.show_tabs)
        CatSetTabs(table);
    if (flags.show_nonprinting)
        CatSetNonpriting(table);
    Cat(argc, argv, flags, table);

    return 0;
}