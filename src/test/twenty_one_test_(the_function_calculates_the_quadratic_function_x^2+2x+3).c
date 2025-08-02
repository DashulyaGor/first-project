#include <stdio.h>

/* we defined a function named foo (we came up with the name ourselves),
It takes a single float type argument and returns a float type result.
*/

float foo(float x){
    float res;
    res = x * x + 2 * x +3;
    return res; //the calculated value was returned
}
// } finished the foo function

int main(){
    float z;
    z = foo(0); //called the foo function for x=0
    printf("f(%f) = %f\n", 0., z);

    z = foo(1); //called the foo function for x=1
    printf("f(%f) = %f\n", 1., z);

    float a;
    scanf("%f", &a);
    z = foo(a); //called the foo function for x=a
    printf("f(%f) = %f\n", a, z);
    return 0;
}