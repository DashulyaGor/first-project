#include <stdio.h>

int main() {
    char s[1000];

    scanf ("%s", s);

    int count = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            count++;
        } else {
            count--;
            if (count < 0) {
                printf("NO\n");
                return 0;
            }
        }
    }

    if (count == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}