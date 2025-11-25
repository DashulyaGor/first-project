#include <stdio.h>
#define N 1000

int main () {
    int a[N];
    int i;
    int n;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (i = n - 1; i >= 0; i--) {
        printf("%d ", a[i]);
    }

    printf("\n");
    return 0;
}