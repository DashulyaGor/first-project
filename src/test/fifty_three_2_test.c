#include <stdio.h>

int main() {
    int x;
    char y;
    char startx, starty;

    scanf("%c%d", &y, &x);

    startx = x;
    starty = y;

    if (y > 'A' && y < 'J' && x > 1 && x < 10) {

    printf("%c%d ", y - 1, startx);

    printf("%c%d ", starty, x + 1);

    printf("%c%d ", y + 1, startx);

    printf("%c%d ", starty, x - 1);

    } else {
        printf("Something went wrong!\n");
    }

    printf("\n");

    return 0;
}