#include <stdio.h>
#include <math.h>

long long fact(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}

int sum(long long n) {
    if (n == 0) {
        return 0;
    }
    return n % 10 + sum(n / 10);
}

int is_prime_helper(int n, int divisor) {
    if (divisor > sqrt(n)) {
        return 1;
    }
    if (n % divisor == 0) {
        return 0;
    }
    return is_prime_helper(n, divisor + 2);
}

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    return is_prime_helper(n, 3);
}

void count_love(int n) {
    static int count = 0;

    if (n == 0) {
        printf("%d\n", count);
        return;
    }
    if (n < 6) {
        long long res = fact(n);
        int a = sum(res);
        int prime = is_prime(a);

        if (prime) {
        count++;
        }
    }

/*
    printf("%d\n", n);
    printf("%lld\n", res);
    printf("%d\n", a);
    printf("%s\n", prime ? "ЛЮБИТ" : "НЕ ЛЮБИТ");
    
    
*/
    count_love(n - 1);
}

int main() {
    int n;

    scanf("%d", &n);

    if (n < 0) {
        return 1;
    }

    count_love(n);

    return 0;
}