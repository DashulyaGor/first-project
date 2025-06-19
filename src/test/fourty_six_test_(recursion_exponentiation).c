#include <stdio.h>


long long int ipow(long long int a, unsigned int n, unsigned int *depth);

int main(){
    long long int x, res;
    unsigned int y, d = 0;
    
    scanf("%lld%u", &x, &y);

    res = ipow(x, y, &d);

    printf("%lld %u\n", res, d);

    return 0;
}

long long int ipow(long long int a, unsigned int n, unsigned int *depth){
    long long int res;
    
    if (n > 0 || n == 0) {
    (*depth)++;
    }

    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return a;
    } else if (n % 2 == 0) {
        res = ipow(a, n / 2, depth);
        return res * res;
    } else {
        res = ipow(a, n / 2, depth);
        return res * res * a;
    }
    return res;
}