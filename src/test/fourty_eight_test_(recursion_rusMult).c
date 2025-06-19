#include <stdio.h>

int rusMult(int a, int b);

int main(){
    int a, b, res;
    scanf("%d%d", &a, &b);
    res = rusMult(a, b);
    printf("%d\n", res);
    return 0;
}

int rusMult(int a, int b) {
    int res, new_res;
    
    if (b == 0) {
        return 0;
    }

    printf("%d %d\n", a, b);

    if (b == 1) {
        printf("%d\n", a);
    }

    if (b > 0) {
        if (b % 2 == 1) {
            res = rusMult(a * 2, b / 2);
            new_res = res + a;
        } else {
            res = rusMult(a * 2, b / 2);
            new_res = res;
        }

    } else {
        return 0;
    }

    if (b != 1) {
    printf("%d %d %d %d\n", res, a, b % 2, new_res);
    }

    return new_res;
}