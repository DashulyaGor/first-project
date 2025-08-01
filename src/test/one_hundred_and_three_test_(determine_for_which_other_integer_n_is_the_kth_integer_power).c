#include <stdio.h>

int power(int a, int n) {
    int result = 1;
    for (int i = 0; i < n; ++i) {
        result *= a;
    }
    return result;
}

int main() {
    int n, k, result = 1, a = 2;
    
    scanf("%d %d", &n, &k);
    int current_quotient = n;

    for (a = 2; a * a <= n; a++) {
        int exponentiation = power(a, k);
    
        if (exponentiation > current_quotient) {
            break;
        }
        
        for (int i = 1; current_quotient % exponentiation == 0; i++) {
            current_quotient /= exponentiation;
            printf("%d %d\n", a, current_quotient);
            result *= a;
        }
    }

    if (current_quotient > 1) {
        int exponentiation = power(current_quotient, k);
        if (exponentiation != current_quotient) {
            printf("-1\n");
            return 0;
        }
        result *= current_quotient;
    }

    printf("%d\n", result);
    return 0;
}