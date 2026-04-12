#include <stdio.h>

#define N 100

typedef struct {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
}Decimal;

void elong_set (Decimal * res, const char str[ ]);

void elong_print(Decimal x) {
    for (int i = x.n; i >= 0; i--) {
        printf("%d", x.a[i]);
    }
    printf("\n");
}

int main(){
    Decimal res;
    elong_set(&res, "12345678901234567890");  // res = 12345678901234567890

    elong_print(res);                         // print 12345678901234567890

    return 0;
}

void elong_set(Decimal *res, const char str[]) {
    // Обнуляем массив
    for (int i = 0; i < N; i++) {
        res->a[i] = 0;
    }

    // Находим длину строки
    int len = 0;
    while (str[len] != '\0') len++;

    // Если строка пустая — считаем числом 0
    if (len == 0) {
        res->n = 0;
        return;
    }

    // Заполняем массив a: с конца строки — в начало массива
    for (int i = 0; i < len; i++) {
        char c = str[len - 1 - i];  // читаем символ с конца строки
        if (c >= '0' && c <= '9') {
            res->a[i] = c - '0';    // преобразуем в цифру
        }
        // Можно добавить проверку на ошибку, если не цифра
    }

    // Определяем n — индекс старшей ненулевой цифры
    // Идём с конца массива a, пока не найдём ненулевую цифру
    int last_nonzero = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (res->a[i] != 0) {
            last_nonzero = i;
            break;
        }
    }
    res->n = last_nonzero;
}