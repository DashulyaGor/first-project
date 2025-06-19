#include <stdio.h>

int main() {
    int SU, a, b;

    scanf("%d:%d", &a, &b);

    if(a > b) {
        SU = 2;
        //printf("%d %d\n%d", a, b, SU);
    }
    if(a == b) {
        SU = 1;
    }
    if(a < b) {
        SU = 0;
    }

    printf("%d:%d\n%d\n", a, b, SU);

    return 0;
}