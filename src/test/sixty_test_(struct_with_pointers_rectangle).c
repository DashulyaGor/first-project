#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

struct Rect {
    struct Point lt;
    struct Point rb;
};

void move(struct Rect * p, int dx) {
    p -> lt.x = p -> lt.x + dx;
    p -> rb.x = p -> rb.x + dx;
}

int main() {
    struct Rect a;
    int dx;
    scanf("%d%d%d%d%d", &a.lt.x, &a.lt.y, &a.rb.x, &a.rb.y, &dx);
    printf("%d %d %d %d + %d = ", a.lt.x, a.lt.y, a.rb.x, a.rb.y, dx);
    move(&a, dx);
    printf("%d %d %d %d\n", a.lt.x, a.lt.y, a.rb.x, a.rb.y);
    return 0;
}