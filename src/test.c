#include <stdio.h>

int main() {
    int i = 10;
    
    while(i > 0) {
        if (i == 1) {
            break;
        }
        printf("%d ", i--);
    }
    printf("\n");

    return 0;
}