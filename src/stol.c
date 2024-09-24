#include <stdio.h>


int main() {
    float n, k; 
    int stol;
    scanf("%f%f", &n, &k);

    stol = (n / 5 + k / 5);

    if (n >= 4 && k >= 1) {
        printf("%d", stol);
    } else if (n < 4 || k < 1 ) {
        printf("0");
    }
    return 0;
}