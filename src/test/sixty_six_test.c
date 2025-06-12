#include <stdio.h>

int main() {
    int n, k, reisov, ostalos;

    scanf("%d%d", &n, &k);

    reisov = n / k;
    ostalos = n % k;

    if (ostalos > 0) {
        reisov += 1;
        printf("Need an additional flight\n");
    }

    printf ("%d\n", reisov);
    return 0;
}