#include <stdio.h>

int main() {

    int v1;    // км/ч
    float v2;  // м/с
    
    scanf("%d", &v1);
    
    v2 = (float)v1 * 1000 / 3600;
        
    printf("%f\n", v2);
    
    return 0;
}