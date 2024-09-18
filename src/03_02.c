#include <stdio.h>
#include <math.h>

int main() {
    double radian, degree;

    if (scanf("%lf", &radian) == 1) {
        degree = 57.29 * radian;
        printf("%.0lf", roundf(degree));
    } else {
        printf("n/a");
    }
    return 0;
}