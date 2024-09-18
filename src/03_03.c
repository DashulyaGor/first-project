#include <stdio.h>
#include <math.h>


int main() {
    int x, first, second, third;
    int flag = 1;

    if (scanf("%d", &x) == 1) {
        if (x < 0) {
            flag =0;
            x = -x;
        }

        third = x % 10;
        x = x / 10;
        second = x % 10;
        first = x / 10;

        if (flag == 1) {
            printf("%d%d%d", third, second, first);
        } else {
            printf("-%d%d%d", third, second, first);
        }
    } else {
        printf("n/a");
    }
    return 0;
}