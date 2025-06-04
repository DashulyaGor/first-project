#include <stdio.h>
#include <math.h>

float dist(int x1, int y1, int x2, int y2);
float area(int x1, int y1, int x2, int y2, int x3, int y3);

int main(){
    int x1, y1, x2, y2, x3, y3; //coordinates of the points
    float S; //square

    scanf("%d%d", &x1, &y1);
    scanf("%d%d", &x2, &y2);
    scanf("%d%d", &x3, &y3); //Read the numbers

    S = area(x1, y1, x2, y2, x3, y3); //calling the area function

    printf("%.3f\n", S); //print the square
    return 0;
}

float dist(int x1, int y1, int x2, int y2){

    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

float area(int x1, int y1, int x2, int y2, int x3, int y3){
    float a, b, c; // sides of the triangle

    a = dist(x1, y1, x2, y2); //calling the dist function for side a
    b = dist(x2, y2, x3, y3); //calling the dist function for side b
    c = dist(x1, y1, x3, y3); //calling the dist function for side c

    float p = (a + b + c) / 2; // half perimeter

    return sqrt(p * (p - a) * (p - b) * (p - c)); //counting the square of the triangle
}