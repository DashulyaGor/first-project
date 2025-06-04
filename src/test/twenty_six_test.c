#include <stdio.h>
#include <assert.h>
#include <math.h>
#define EPS 0.0001

//compares the numbers a and b with an accuracy of EPS


float fahr(int cel){
    return (cel * 1.8) + 32;
}

int eps(float a, float b){
    //float res;
    //if(fabs(a - b) < EPS){
    //res = fabs(33.8 - fahr(1)) < EPS;
    //}
    return fabs(a - b) < EPS;
}

int main(){
    int cel;
    float f;

    //tests
    assert(32 == fahr(0));
    assert(122 == fahr(50));
    assert(-40 == fahr(-40));
    //printf("C = %d, F = %.2f\n", 1, fahr(1));
    assert(eps(33.8, fahr(1)));

    //for an arbitrary number
    scanf("%d", &cel);
    f = fahr(cel);
    printf("C = %d, F = %.2f\n", cel, f);

    return 0;
}