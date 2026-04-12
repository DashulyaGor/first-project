#include <stdio.h>

#define N 100
typedef struct {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
}Decimal;

void str_to_decimal (char *s, Decimal *num);
Decimal add (Decimal x, Decimal y);
void elong_print(Decimal x);
int main() {

    Decimal x;
    Decimal y;
    Decimal res;
    char input[N];

    scanf("%s", input);           // input = "147"
    str_to_decimal (input, &x);   // x = 147

    scanf("%s", input);
    str_to_decimal (input, &y);

    res = add(x, y);             // res = x+y = 147+13 = 160
    elong_print(res);            // print 160

    return 0;
}

void str_to_decimal (char *s, Decimal *num) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    //Обнуляем массив
    for (int i = 0; i < N; i++) {
        num->a[i] = 0;
    }
    //Если строка пустая
    if (len == 0) {
        num->n = 0;
        num->a[0] = 0;
        return;
    }
    //Записываем цифры в обратном порядке: млфдшая - в a[0], старшая - в a[n]
    for (int i = 0; i < len; i++) {
        num->a[i] = s[len - i - 1] - '0'; //символ -> число
    }

    num->n = len - 1; //степень старшей цифры
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