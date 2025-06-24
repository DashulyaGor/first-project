#include <stdio.h>


long long int ipow(long long int a, unsigned int n);
void exponent_property(long long int a, long long int b, unsigned int n);

int main() {
    long long int x;
    unsigned int y, z;
    
    scanf("%lld%u%u", &x, &y, &z);

    exponent_property(x, y, z);

    return 0;
}

long long int ipow(long long int a, unsigned int n){
    long long int res = 1;
    
    if (n == 0) {
        return a = 1;
    } else if (n == 1) {
        return a;
    } else if (n % 2 == 0) {
        res = ipow(a, n / 2);
        return res * res;
    } else {
        res = ipow(a, n / 2);
        return res * res * a;
    }
    return res;
}

void exponent_property(long long int a, long long int b, unsigned int n) {
    long long int left_side = ipow(a * b, n);
    long long int right_side = ipow(a, n) * ipow(b, n);

    if (left_side == right_side) {
        printf("The property is fulfilled:\n");
        printf("(%lld * %lld) ^ %u = %lld\n", a, b, n, left_side);
        printf("%lld ^ %u * %lld ^ %u = %lld\n", a, n, b, n, right_side);
        printf("%lld = %lld\n", left_side, right_side);
    } else {
        printf("Calculation error!\n");
    }
}