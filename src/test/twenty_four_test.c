#include <stdio.h>

float celsius(int fahr){
    float res;
    res = (fahr - 32) / 1.8;
    return res;
}

int main(){
    int fahr;
    float cel;

    //test
    fahr = 32;
    cel = celsius(fahr);
    printf("F = %d, C = %.4f\n", fahr, cel);

    //for an arbitrary number
    scanf("%d", &fahr);
    cel = celsius(fahr);
    printf("F = %d, C = %.4f\n", fahr, cel);

    return 0;
}