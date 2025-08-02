#include <stdio.h>

int main() {
    int z, s;

    scanf("%d", &z);

    if (z < 10) {
        s = 0;
        printf("%d\n", s);
    }
    if (z >= 10 && z <= 12) {
        s = 3;
        printf("%d\n", s);
    }
    if (z >= 13 && z <= 15) {
        s = 5;
        printf("%d\n", s);
    }
    if (z > 15) {
        s = 10;
        printf("%d\n", s);
    }

    return 0;
}