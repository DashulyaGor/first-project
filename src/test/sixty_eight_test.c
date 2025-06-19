#include <stdio.h>

int main() {
    int n, k_rice, k_veg;

    scanf("%d%d%d", &n, &k_rice, &k_veg);
    printf("%d %d %d\n", n, k_rice, k_veg);

    int cost = k_rice + k_veg * 2;
    printf("%d\n", cost);

    if (n >= cost) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}