#include <stdio.h>

int main() {
    int x, y;
    scanf("%d%d", &x, &y);

    if (x < y) {
        printf("%d %d\n%d\n", x, y, x);
    } else {
        printf("%d %d\n%d\n", x, y, y);
    }

    return 0;
}