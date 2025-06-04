#include <stdio.h>

int main(){
    int rub, kop;

    scanf("%d%d", &rub, &kop);

    int n = (rub * 100 + kop) / 106;

    int rest = (rub * 100 + kop) % 106;

    printf("%d %d\n", n , rest);

    return 0;
}