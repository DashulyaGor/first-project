#include <stdio.h>
#define N 1000

int main () {
    int a[N];
    int i;
    int n;
    int k;
    int found = 0;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    scanf("%d", &k);

    for (i = 0; i < n; i++) {
        if (a[i] ==k) {
            found = 1;
            printf("%d\n", i);
            break;
        }
    }

    if (!found) {
        printf("-1\n");
    }

    return 0;
}