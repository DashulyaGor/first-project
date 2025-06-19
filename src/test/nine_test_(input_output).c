#include <stdio.h>

int main() {

    int x, y, res1, res2;

    scanf("%d%d", &x, &y);

    res1 = x / y;
    res2 = x % y;

    printf("%d\n%d\n", res1, res2);

    return 0;
}