#include <stdio.h>


int main()
{
    int SU, a1, b1, a2, b2, sum_a, sum_b;

    scanf("%d:%d", &a1, &b1);
    scanf("%d:%d", &a2, &b2);

    sum_a = a1 + a2;
    sum_b = b1 + b2;

    if(sum_a > sum_b) {
        SU = 2;
    }
    if(sum_a == sum_b) {
        SU = 1;
    }
    if(sum_a < sum_b) {
        SU = 0;
    }

    printf("%d:%d\n%d\n", sum_a, sum_b, SU);

    return 0;
}