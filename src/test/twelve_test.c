#include <stdio.h>

int main() {

    int round, distance;

    scanf("%d%d", &round, &distance);

    int circle = distance / round;

    int finish = distance % round;

    printf("%d %d\n", circle, finish);

    return 0;
}