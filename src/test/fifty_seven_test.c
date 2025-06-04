#include <stdio.h>

struct Rect {
    int x;
    int y;
    int width;
    int height;
};

int area(struct Rect a) {
    return a.width * a.height;
}

int main() {
    struct Rect a = {-7, 5, 12, 8};
    int s = area(a);
    printf("%d %d %d %d %d\n", a.x, a.y, a.width, a.height, s);
    return 0;
}