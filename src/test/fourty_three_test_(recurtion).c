#include <stdio.h>

int delim_konfety(int a);

int main() {
    int konfet;
    scanf("%d", &konfet);

    int detey = delim_konfety(konfet);
    printf("%d\n", detey);

    return 0;
}

int delim_konfety(int a) {
    static int n; //number of children

    if (a > 1){
        n = delim_konfety(a - a / 2);
    }
    n++;
    return n;
}