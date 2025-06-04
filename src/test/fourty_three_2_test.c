#include <stdio.h>

int delim_konfety(int a, int depth);

int main() {
    int konfet;
    scanf("%d", &konfet);

    int detey = delim_konfety(konfet, 1);
    printf("%d\n", detey);
    //printf("main: delim_konfety(%d) = %d\n", delim_konfety(konfet, 1), detey);

    return 0;
}

int delim_konfety(int a, int depth) {
    static int n; //number of children
    printf("%-*c call delim_konfety(%d)\n", depth, '>', a);

    if (a > 1){
        n = delim_konfety(a - a / 2, depth + 2);
    }
    n++;
    printf("%-*c delim_konfety(%d) = %d\n", depth, '>', a, n);
    return n;
}