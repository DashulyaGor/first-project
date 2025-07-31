#include <stdio.h>

int main() {
    int n, number, min;

    scanf("%d", &n);
    scanf("%d", &number);
    min = number;

    for (int i = 1; i < n; ++i) {
        
        scanf("%d", &number);

        if (number < min) {
            min = number;
        }
    }

    printf("%d\n", min);
    return 0;
}