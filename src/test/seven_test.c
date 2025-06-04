#include <stdio.h>

int main() {
    int k_rice, k_veg, res;

    scanf("%d%d", &k_rice, &k_veg);

    res = k_rice + k_veg * 2;

    printf("%d\n", res);

    return 0;
}