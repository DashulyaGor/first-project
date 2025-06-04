#include <stdio.h>

int main() {
    int n;  //всего кругов
    float k;  //отношение скорости первого к скорости второго коэф

    scanf("%d%f", &n, &k);

    int n2 = n * k;

    float ratio = n % n2;

    int match = n - n2 - (int)ratio;

    printf("%d\n", match);

    return 0;
}