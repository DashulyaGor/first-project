#include <stdio.h>
#include <math.h>
#include "twenty_test.h"

int main(){
    double 
    a, //the angle to the horizon, in DEGREES, at which the body was thrown
    v0, //initial velocity of the body, m/s
    g = 9.81, //acceleration of free fall
    h; //maximum lifting height of the body

    // h = v0 * v0 * sin(a) * sin(a) / (2 * g);

    //reading the input data
    scanf("%lf", &a);
    scanf("%lf", &v0);

    //sin is calculated from radians, degrees are given
    //convert degrees to radians rad = degree * (M_PI / 180.0)
    //M_PI is the number PI, defined in the standard mathematical library

    double arad = a * (M_PI / 180.0);
    h = (v0 * v0 * sin(arad) * sin(arad) / (2 * g));

    printf("Maximum lifting height %lf m\n", h);
    return 0;
}