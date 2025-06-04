#include <stdio.h>

int main(){
    int bell, nbell, total;

    scanf("%d%d", &bell, &nbell);

    int summ = bell + nbell;

    int hours = (nbell - bell) + 1;

    int strokes = summ * hours;

    total = strokes / 2;

    printf("%d\n", total);

    return 0;
}