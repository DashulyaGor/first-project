#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int d;
    char k_str[1000];
    int count = 0;

    scanf("%d", &d);
    scanf("%s", k_str);

    char original_k_str[1000];
    strcpy(original_k_str, k_str);

    for (int i = 0; k_str[i] != '\0'; ++i) {
        if (!isdigit(k_str[i])) {
            printf("Error: The input contains invalid characters.\n");
            return 1;
        }
    }

    for (int i = 0; k_str[i] != '\0'; ++i) {
        if (k_str[i] == '0' + d) {
            count++;
        }
    }

    printf("%d %s %d\n", d, original_k_str, count);
    return 0;
}