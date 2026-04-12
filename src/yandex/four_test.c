#include <stdio.h>

int main() {
    long long a, b, c;
    scanf("%lld", &a);
    scanf("%lld", &b);
    scanf("%lld", &c);

    // Случай: c < 0
    if (c < 0) {
        printf("NO SOLUTION\n");
        return 0;
    }

    // Случай: c >= 0
    long long c2 = c * c;      // c^2
    long long rhs = c2 - b;    // ax = rhs

    if (a == 0) {
        if (rhs == 0) {
            printf("MANY SOLUTIONS\n");
        } else {
            printf("NO SOLUTION\n");
        }
        return 0;
    }

    // a != 0
    // Проверяем, делится ли rhs на a нацело
    // Учитываем знак: используем остаток
    if (rhs % a != 0) {
        printf("NO SOLUTION\n");
        return 0;
    }

    long long x = rhs / a;

    printf("%lld\n", x);

    return 0;
}