#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int k = (n - 1) % 4;

    if (k == 0) {
        printf("-1\n");
    } else {
        printf("%d\n", k);
    }

    return 0;
}