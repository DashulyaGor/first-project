#include <stdio.h>

typedef struct Circle {
    int x;
    int y;
    double r;
} Circle;


Circle zoom(Circle c, int k);

int main()
{
    Circle c = {1, 2, 3};
    Circle z = zoom(c, 5);
    printf("%.0lf\n", z.r);
    return 0;
}

Circle zoom(Circle c, int k)
{
    Circle res = c;
    res.r *= k;
    return res;
}