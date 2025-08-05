#include <stdio.h>

int main() {
    int d, count = 0;
    long k, first_k;

    scanf("%d%ld", &d, &k);

    first_k = k;

    for (; k != 0; k /= 10) {
        int last_k = k % 10;
        if (last_k == d) {
            count++;
        }
    }
    printf("%d %ld %d\n", d, first_k, count);
    return 0;
}