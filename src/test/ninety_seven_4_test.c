#include <stdio.h>

int pikup_1row() {
    int x; //яблок на одной (текущей) яблоне
    int sum; //уже собрали яблок
    int n; //количество деревьев
    int i; //сколько деревьев уже обработали

    scanf("%d", &n);

    sum = 0; //не забыть очистить корзину перед сбором яблок!
    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        sum += x;
        printf("apple tree %d: x is %d and sum is %d \n", i, x, sum);
    }
    return sum;
}

int main() {
    printf("%d\n", pikup_1row());
    return 0;
}