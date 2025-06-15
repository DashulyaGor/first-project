#include <stdio.h>

float solve_linear_equation(float a, float b) {
    float x;
    if(a == 0) {
        if(b != 0) {
            printf("The equation has no solutions\n");
        } else {
            printf("Any value of x is a solution to the equation\n");
        }
    } else {
        x = b / a;
    }
    return x;
}

int main() {
    float a, b;
    float x;

    scanf("%f%f", &a, &b);

    x = solve_linear_equation(a, b);

    if(a != 0) {
    printf("x = %.02f\n", x);
    }

    return 0;
}