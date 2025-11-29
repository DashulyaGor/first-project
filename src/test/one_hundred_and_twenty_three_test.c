#include <stdio.h>
#define N 1000

int main() {
    int a[N];
    int b[N];
    int i;
    int n;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    for (i = 0; i < n; i++) {
        printf ("%d", a[i] + b[i]);
        if (i < n - 1) {
            printf (" ");
        }
    }
    printf("\n");

    return 0;
}