#include <stdio.h>

#define N 100
typedef struct {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
}Decimal;

Decimal add (Decimal x, Decimal y);
void elong_print(Decimal x);
int main() {

    Decimal x = {{7, 4, 1}, 2};  // set number 147
    Decimal y = {{3, 1}, 1};     // set number 13
    Decimal res;

    res = add(x, y);             // res = x+y = 147+13 = 160
    elong_print(res);            // print 160

    return 0;
}

Decimal add (Decimal x, Decimal y) {
    Decimal res;
    int carry = 0;
    unsigned int i;

    // Обнуляем массив
    for (i = 0; i < N; i++) {
        res.a[i] = 0;
    }

    // Сложение
    for (i = 0; i <= x.n || i <= y.n || carry; i++) {
        int digit = carry;
        if (i <= x.n) {
            digit += x.a[i];
        }
        if (i <= y.n) {
            digit += y.a[i];
        }

        carry = digit / 10;
        res.a[i] = digit % 10;
        res.n = i;
    }

    return res;
}

void elong_print(Decimal x) {
        // Выводим число
        printf("n: %u\n", x.n);
        for (int i = x.n; i >= 0; i--) {
            printf("%d", x.a[i]);
        }
        printf("\n");
}