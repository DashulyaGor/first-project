#include <stdio.h>

long long fast_ipow(long long a, unsigned int n) {
    long long res = 1;
    while(n > 0) {
        if (n % 2 != 0) {
            res *= a;
        }
        a *= a;
        n /= 2;
    }
    return res;
}

double ipow(double a, int n) {
    if (n == 0) {
        return 1;
    } else if (n < 0) {
        return 1 / fast_ipow(a, -n);
    } else {
        return fast_ipow(a, n);
    }
}

int main() {
    double a;
    int n;
    printf("Enter the base: ");
    scanf("%lf", &a);
    printf("Enter the degree indicator: ");
    scanf("%d", &n);

    double res = ipow(a, n);
    printf("%.1f ^ %d = %.1f\n", a, n, res);

    return 0;
}