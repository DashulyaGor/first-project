#include <stdio.h>

#define XLEN (('9' + 1) - '1')
#define XSTART ('1' % XLEN)
#define YLEN ('J' - 'A')
#define YSTART ('A' % YLEN)

int x_move(int letter, int shift);
int y_move(int letter, int shift);

int main() {
    int shift = 1;
    char x, y;
    char left, down, right, up;

    scanf("%c%c", &x, &y);

    if (x >= '2' && x <= '9') {
        left = x_move(x, x - shift);
        right = x_move(x, x + shift);
    }
    if (y >= 'B' && y <= 'I') {
    down = y_move(y, y - shift);
    up = y_move(y, y + shift);
    }

    if (up != '\0') {
        printf("%c%c ", up, x);
    }
    if (right != '\0') {
        printf("%c%c ", y, right);
    }
    if (down != '\0') {
        printf("%c%c ", down, x);
    }
    if (left != '\0') {
        printf("%c%c ", y, left);
    }

    printf("\n");

    return 0;
}

int x_move(int letter, int shift) {
    return '1' + (letter - XSTART + (shift % XLEN)) % XLEN;
}

int y_move(int letter, int shift) {
    return 'A' + (letter - YSTART + (shift % YLEN)) % YLEN;
}