#include <stdio.h>

#define N 100
typedef struct {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
}Decimal;

void elong_print(Decimal x);
int main()
{
    Decimal x;

    for (int i = 0; i < N; i++) {
        x.a[i] = 0;
    }

    char input[N];
    scanf("%s", input);

    int len = 0;
    while(input[len] != '\0')
    len++;

    if(len == 0) {
        printf("\n");
        return 0;
    }

    for (int i = 0; i < len; i++) {
        x.a[i] = input[len - i - 1] - '0';
    }

    x.n = len - 1;

    elong_print(x);

    return 0;
}

void elong_print(Decimal x) {
        for (int i = x.n; i >= 0; i--) {
            printf("%d", x.a[i]);
        }
        printf("\n");
}