#include <stdio.h>
#include <stdlib.h>

struct Rect {
    int x;
    int y;
    int width;
    int height;
};

void move(struct Rect * p, int dx) {
    p -> x = p -> x + dx;
}

int main() {
    struct Rect a;
    int dx;
    scanf("%d%d%d%d%d", &a.x, &a.y, &a.width, &a.height, &dx);
    printf("%d %d %d %d + %d = ", a.x, a.y, a.width, a.height, dx);
    move(&a, dx);
    printf("%d %d %d %d\n", a.x, a.y, a.width, a.height);
    return 0;
}