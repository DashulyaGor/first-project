#include <stdio.h>
#include <math.h>

/*
int main() {
    int n = 4.7;
    int k = (int)5.7;

    float a = 3;
    float b = (float)4;

    printf("%d %d %.2f %.2f\n", n, k, a, b);

    return 0;
}
*/
/*
int main() {

    int round, distance;

    scanf("%d%d", &round, &distance);

    int circle = distance / round;

    int finish = distance % round;

    printf("%d %d\n", circle, finish);

    return 0;
}
*/
int main() {
    int n;
    float k;
    scanf("%d%f", &n, &k);

    //int n2 = n * k;
    //float ratio = n % n2;
    //int match = n - n2 - (int)ratio;
    int match = n * (1 - k);

    printf("%d\n", match);

    return 0;
}