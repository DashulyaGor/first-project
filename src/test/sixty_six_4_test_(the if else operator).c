#include <stdio.h>

int main() {
    int x;
    scanf("%d", &x);
    if(x % 2 == 1)
        printf("odd number\n");
    else
        printf("even number\n");
    return 0;
}