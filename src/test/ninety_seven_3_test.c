#include <stdio.h>

int main() {
    int x;
    int sum;
    int n;
    int i;
    //int v = 5;

    scanf("%d", &n);

    sum = 0;
    for(i = 0; i < n; i++) {
        scanf("%d", &x);
        //sum += x;
        //sum -= v;
        if (x < 0) {
            printf("ВОРОНЫ!\n");
            continue;
        }
        sum += x;
        printf("apple tree %d: x is %d and sum is %d\n", i, x, sum);
    }

    printf("%d\n", sum);
    return 0;
}