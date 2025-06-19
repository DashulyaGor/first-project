#include <stdio.h>

int rusDel(int a, int b);

int main(){
    int a, b, res;
    
    scanf("%d%d", &a, &b);

    res = rusDel(a, b);

    printf("%d\n", res);

    return 0;
}

int rusDel(int a, int b) {
    int mult, rem, part, new_part;

    if (a < b) {
        return 0;
    }

    if (a % 2 == 0) {
        mult = 2;
        rem = 0;
        a /= 2;
    } else {
        mult = 1;
        rem = 1;
        a -= b;
    }

    if (a == 0) {
        printf("%d\n", 1);
        return 1;
    }

    printf("%d %d %d\n", a, mult, rem);

    part = rusDel(a, b);
    new_part = part * mult + rem;

    if (a != 0) {
    printf("%d * %d + %d = %d\n", part, mult, rem, new_part);
    }
    return new_part;
}