#include <stdio.h>

int main() {
    int x;
    int sum = 0;
    int n;
    int i;

    scanf("%d", &n);
    i = 0;
    
    while(i < n) {
        scanf("%d", &x);
        sum += x;
        printf("x is %d and sum is %d\n", x, sum);
        i++;
    }

    printf("%d\n", sum);
    return 0;
}