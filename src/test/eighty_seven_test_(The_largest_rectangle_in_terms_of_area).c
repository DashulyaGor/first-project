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

int area(struct Rect a);
struct Rect *max(struct Rect *pa, struct Rect *pb);


int main() {
    struct Rect a, b;
    int Sa, Sb;

    scanf("%d%d%d%d", &a.lt.x, &a.lt.y, &a.rb.x, &a.rb.y);
    scanf("%d%d%d%d", &b.lt.x, &b.lt.y, &b.rb.x, &b.rb.y);

    Sa = area(a);
    Sb = area(b);

    struct Rect* max_area = max(&a, &b);

    printf("%d %d %d %d %d\n", a.lt.x, a.lt.y, a.rb.x, a.rb.y, Sa);
    printf("%d %d %d %d %d\n", b.lt.x, b.lt.y, b.rb.x, b.rb.y, Sb);

    if (max_area == &a) {
        printf("%d\n", area(a));
    } else {
        printf("%d\n", area(b));
    }

    return 0;
}

int area(struct Rect a) {
    return (abs(a.lt.x - a.rb.x) * abs(a.lt.y - a.rb.y));
}

struct Rect *max(struct Rect *pa, struct Rect *pb) {
    if (area(*pa) >= area(*pb)) {
        return pa;
    } else {
        return pb;
    }
}