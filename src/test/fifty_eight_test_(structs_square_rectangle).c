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

int area(struct Rect a) {
    return (abs(a.lt.x - a.rb.x) * abs(a.lt.y - a.rb.y));
}

int main() {
    struct Rect a = {{-7, 5}, {5, -3}};
    int s = area(a);
    printf("%d %d %d %d %d\n", a.lt.x, a.lt.y, a.rb.x, a.rb.y, s);
    return 0;
}