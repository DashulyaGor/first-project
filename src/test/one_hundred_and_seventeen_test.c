#include <stdio.h>
#define N 10

int main() {
    int a[N];
    int i, k, n, sum = 0;

    for (i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    scanf("%d %d", &k, &n);

    for (i = 0; i < N; i++) {
        if (k <= i && i < n) {
            sum += a[i];
        }
    }

    printf("%d\n", sum);

    return 0;
}