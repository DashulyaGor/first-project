#include <stdio.h>

int main(){
    int g, s, k, g1, s1, k1, g2, s2, k2;

    scanf("%d%d%d\n%d%d%d", &g1, &s1, &k1, &g2, &s2, &k2);

    int g0 = 17;
    int s0 = 29;

    k = (k1 + k2) % s0;
    s = (((k1 + k2) / s0) + (s1 + s2)) % g0;
    g = (s1 + s2 + ((k1 + k2) / s0)) / g0 + (g1 + g2);

    printf("%d %d %d\n", g, s, k);

    return 0;
}