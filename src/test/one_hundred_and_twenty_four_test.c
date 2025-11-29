#include <stdio.h>
#define N 1000

int main () {
    int a[N];
    int b[N];
    int i;
    int n;
    long int sum = 0;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    for (i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }

    printf("%ld\n", sum);

    return 0;
}