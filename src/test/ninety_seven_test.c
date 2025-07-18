#include <stdio.h>

int main() {
    int x;
    int sum = 0;

    //первая яблоня
    scanf("%d", &x);
    sum += x;
    printf("x is %d and sum is %d\n", x, sum);

    //вторая яблоня
    scanf("%d", &x);
    sum += x;
    printf("x is %d and sum is %d\n", x, sum);

    //последняя яблоня
    scanf("%d", &x);
    sum += x;
    printf("x is %d and sum is %d\n", x, sum);

    printf("%d\n", sum);
    return 0;
}