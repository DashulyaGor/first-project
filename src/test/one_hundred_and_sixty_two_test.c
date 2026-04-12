#include <stdio.h>
#include <assert.h>

int main() {
    int x;
    int i;
    int a[5];

    scanf("%d", &x);
    scanf("%d", &i);
    scanf("%d", &a[i]);

    assert(x - a[i] == 0);

    printf("%d %d\n", x, a[i]);
}