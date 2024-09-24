#include <stdio.h>

int main() {
    int n, max = 0;
    char end;

    if (scanf("%d%c", &n, &end) == 2 && (end == '\n' || end == EOF)) {

        if (n < 0) {
            n = -n;
        }

        while(n > 0) {
            if(n % 10 > max) {
                max = n % 10;
            }
            n = n / 10;
        }

        printf("%d", max);
    } else {
        printf("n/a");
    }
    return 0;
}