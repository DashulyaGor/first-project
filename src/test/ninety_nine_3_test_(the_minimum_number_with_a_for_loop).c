#include <stdio.h>

int main() {
    int n, number, min;

    scanf("%d", &n);
    scanf("%d", &number);
    min = number;
    printf("%d ", number);

    for (int i = 1; i < n; ++i) {
        
        scanf("%d", &number);
        printf("%d ", number);

        if (number < min) {
            min = number;
        }
    }

    printf("\n%d\n", min);
    return 0;
}