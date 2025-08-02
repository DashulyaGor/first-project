#include <stdio.h>

int main() {
    int n, k, s;
    scanf("%d%d", &n, &k);

    if (n != 0) {
        s = n / 4;
    } else {
        s = n;
    }

    if (s <= k && k != 0) {
        printf("%d\n", s);
    } else {
        printf("%d\n", k);
    }

    return 0;
}