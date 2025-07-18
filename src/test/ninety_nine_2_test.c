#include <stdio.h>

int main() {
    int n, count = 0, number;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &number);
        if (number % 2 == 0) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}