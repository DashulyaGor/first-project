#include <stdio.h>


double ipow(double a, int n);
void exponent_property(double a, int m, int n);

int main() {
    double x;
    int y, z;
    
    scanf("%lf%d%d", &x, &y, &z);

    exponent_property(x, y, z);

    return 0;
}

double ipow(double a, int n){
    double res = 1;
    
    if (n == 0) {
        return a = 1;
    } else if (n == 1) {
        return a;
    } else if (n < 0) {
        res = 1 / ipow(a, -n);
    } else if (n % 2 == 0) {
        res = ipow(a, n / 2);
        return res * res;
    } else {
        res = ipow(a, n / 2);
        return res * res * a;
    }
    return res;
}

void exponent_property(double a, int m, int n) {
    double left_side = ipow(a, m) / ipow(a, n);
    double right_side = ipow(a, m - n);

    if (a == 0) {
        left_side = 0;
        right_side = 0;
    }

    if (left_side == right_side) {
        printf("The property is fulfilled:\n");
        printf("%.2lf ^ %d / %.2lf ^ %d = %.2lf\n", a, m, a, n, left_side);
        printf("%.2lf ^ (%d - %d) = %.2lf\n", a, m, n, right_side);
        printf("%.2lf = %.2lf\n", left_side, right_side);
        
    } else {
        printf("Calculation error!\n");
    }
}