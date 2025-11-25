#include <stdio.h>
#define N 5

int main() {

    int a[N];
    int i, sum = 0;

    for (i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    printf("%d\n", sum);

    return 0;
}