#include <stdio.h>

int main() {
    float m;
    int hsm;

    scanf("%f%d", &m, &hsm);

    float hm = (float)hsm / 100;

    float imt = m / (hm * hm);

    printf("%f\n", imt);

    return 0;
}