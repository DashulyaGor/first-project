#include <stdio.h>

int main() {
    int w, x, y, x2, y2, z, a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    x = c * (a + b);
    y = c * a + c * b;
    x2 = c * (a - b);
    y2 = c * a - c * b;
    w = c * (a * b);
    z = a * (b * c);

    if (x == y && x2 == y2 && w == z) {
        if (x == y)
            printf("x(%d) = y(%d) SUCCESS\n", x, y);
        if (x2 == y2)
            printf("x2(%d) = y2(%d) SUCCESS\n", x2, y2);
        if (w == z)
            printf("w(%d) = z(%d) SUCCESS\n", w, z);
        
    } else {
        printf("FAILURE\n");
    }

    return 0;
}