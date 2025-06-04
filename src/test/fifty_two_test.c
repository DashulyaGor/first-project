#include <stdio.h>

int main() {
    char x, y;

    scanf("%c%c", &x, &y);

    if ('1' <= y && y <= '7')
        y++;

    printf("%c%c\n", x, y);

    return 0;
}