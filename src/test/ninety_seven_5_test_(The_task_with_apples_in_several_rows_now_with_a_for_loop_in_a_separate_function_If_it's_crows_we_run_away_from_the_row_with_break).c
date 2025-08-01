#include <stdio.h>

int pikup_1row() {
    int x; //яблок на одной (текущей) яблоне
    int sum; //уже собрали яблок
    int n; //количество деревьев
    int i; //сколько деревьев уже собрали

    scanf("%d", &n);

    sum = 0; //не забыть очистить корзину перед сбором яблок
    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        if (x < 0) {
            printf("Вороны!\n");
            break;
        }
        sum += x;
        printf("i = %d x = %d sum = %d\n", i, x, sum);
    }
    return sum;
}

int main() {
    int rows; //сколько рядов яблонь
    int j; //сколько рядов уже собрали
    int total; //сколько яблок собрали во всех рядах

    scanf("%d", &rows);

    total = 0;
    for (j = 0; j < rows; j++) {
        total += pikup_1row();
        printf("j = %d total = %d\n", j, total);
    }
    printf("%d\n", total);
    return 0;
}