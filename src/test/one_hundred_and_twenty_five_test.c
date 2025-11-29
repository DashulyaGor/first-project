#include <stdio.h>

int main() {
    int a[10] = {0};
    int i;
    int n;
    int color;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &color);
        if (color >= 0 && color <= 9) {
            a[color]++;
        }
    }

    for (i = 0; i < 10; i++) {
        printf("%d %d\n", i, a[i]);
    }

    return 0;
}