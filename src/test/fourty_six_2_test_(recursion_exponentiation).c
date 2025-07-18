#include <stdio.h>

//функция для быстрого возведения числа "a" в степень "n"
double fast_power(double a, int n) {
    if (n == 0) {
        return 1;
    }

    if (n % 2 == 0) {
        double half_pow = fast_power(a, n / 2);
        return half_pow * half_pow;
    } else {
        return a * fast_power(a, n - 1);
    }
}

int main() {
    double base;
    int exponent;

    scanf("%lf%d", &base, &exponent);

    double result = fast_power(base, exponent);
    printf("%.0lf^%d = %.0lf\n", base, exponent, result);

    return 0;
}