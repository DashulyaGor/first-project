#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LEN 100

unsigned long long get_base(int rank) {
    if (rank == 1) return 1;
    if (rank == 2) return 20;
    if (rank == 3) return 18 * 20;
    if (rank == 4) return 18 * 20 * 20;
    if (rank == 5) return 18 * 18 * 20 * 20;  // 129600
    return 18 * 18 * 20 * 20 * (1); // for higher, but not needed
}

int main() {
    char lines[MAX_LINES][MAX_LEN];
    int line_count = 0;

    while (line_count < MAX_LINES) {
        if (fgets(lines[line_count], MAX_LEN, stdin) == NULL) break;
        int len = strlen(lines[line_count]);
        if (len > 0 && lines[line_count][len-1] == '\n') lines[line_count][--len] = '\0';
        if (len == 0) break;
        line_count++;
    }

    if (line_count == 0) {
        printf("0\n");
        return 0;
    }

    unsigned long long total = 0;
    int pos = 0;
    int rank = 1;

    while (pos < line_count) {
        unsigned long long digit = 0;

        if (strcmp(lines[pos], "@") == 0) {
            digit = 0;
            pos++;
        } else {
            int stars = 0, bars = 0;
            if (strchr(lines[pos], '*')) {
                for (int i = 0; lines[pos][i]; i++) if (lines[pos][i] == '*') stars++;
                pos++;
            }
            while (pos < line_count && strcmp(lines[pos], "-") == 0) {
                bars++;
                pos++;
            }
            digit = bars * 5 + stars;
        }

        unsigned long long base = get_base(rank);
        total += digit * base;
        rank++;
    }

    printf("%llu\n", total);
    return 0;
}