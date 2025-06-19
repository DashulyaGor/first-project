#include <stdio.h>

int main()
{
    int a = 2, b = 3;
    int sum = a + b;
    printf("2 + 3 = %d\n", 2+3);            // 2 + 3 = 5
    printf("%d + %d = %d\n", 2, 3, 2+3);
    printf("%d + %d = %d\n", a, b, sum);    // 2 + 3 = 5
    printf("Enter the value \"a\"\n");
    scanf("%d", &a);
    printf("Enter the value \"b\"\n");
    scanf("%d", &b);
    sum = a + b;
    printf("a + b = %d\n", sum);
    printf("Archimedes calculated Pi as %d/%d or %f\n", 22, 7, 3.142857);
    return 0;
}