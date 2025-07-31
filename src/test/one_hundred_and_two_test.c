#include <stdio.h>

int main() {
    long n, rev_num = 0, temp;
    scanf("%ld", &n);

    temp = n;

    for (int i = 0; temp > 0; i++) {
        
        rev_num = rev_num * 10 + temp % 10;
        temp /= 10;

    }

    if (n == rev_num) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}