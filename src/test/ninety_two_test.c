#include <stdio.h>

int main() {
    int k = 1, n;
    int res;

    scanf("%d", &n);

    res = n - k;

    if (res > 1 && k >=1 && k <= 3) {
        k++;
        res = n - k;
        printf("%d = %d - %d\n", res, n, k);
        if (res > 1) {
            k++;
            res = n - k;
            printf("%d = %d - %d\n", res, n, k);
        } else {
            
        }
    } else {
        printf("-1\n");
    }

    return 0;
}