#include <stdio.h>

int main() {
    int n, sum = 0, number;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &number);
        if (number % 2 == 0) {
            sum += number;
        }
    }
    printf("%d\n", sum);
    return 0;
}