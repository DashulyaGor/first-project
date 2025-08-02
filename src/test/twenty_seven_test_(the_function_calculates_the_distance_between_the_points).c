#include <stdio.h>
#include <math.h>

float dist(int x1, int y1, int x2, int y2);

int main(){
    int x1, y1, x2, y2; //coordinates of the points
    float len; //length

    scanf("%d%d", &x1, &y1);
    scanf("%d%d", &x2, &y2); //Read the numbers

    len = dist(x1, y1 , x2, y2); //calling the dist function

    printf("%.3f\n", len); //print the length
    return 0;
}

float dist(int x1, int y1, int x2, int y2){
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}