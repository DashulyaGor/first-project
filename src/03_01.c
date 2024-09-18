#include <stdio.h>
#include <math.h>
#define M_PI 3.141592

int main() {
    double R, m, result;

    if (scanf("%lf", &R) == 1) {
        m = 21500 * (4.0 / 3.0) * M_PI * pow(R, 3);
        result = round(m);
        printf("%.0lf", result); 
    } else {
        printf("n/a");
    }
    return 0;
}