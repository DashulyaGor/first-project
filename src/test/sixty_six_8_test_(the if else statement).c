#include <stdio.h>

int main() {
    int x;
    scanf("%d", &x);
    printf("%d ", x);

    if (x <= 37 || x > 146) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}