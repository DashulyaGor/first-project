#include <stdio.h>
#define N 1000

int main() {
    int a[N];
    int i;
    int n;
    int k;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    scanf("%d", &k);

    for (i = 0; i < n; i++) {
        if (a[i] == k) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}