#include <stdio.h>

int main() {
    int x, y = 0;

    scanf("%d", &x);

    do {
        int last_x = x % 10;
        y = y * 10 + last_x;
        x = x / 10;
    } while (x != 0);

    printf("%d\n", y);

    return 0;
}