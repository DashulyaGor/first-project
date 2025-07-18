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


int is_crossed(struct Rect a, struct Rect b);
struct Rect intersection(struct Rect a, struct Rect b);


int main() {
    struct Rect a, b;

    scanf("%d%d%d%d", &a.lt.x, &a.lt.y, &a.rb.x, &a.rb.y);
    scanf("%d%d%d%d", &b.lt.x, &b.lt.y, &b.rb.x, &b.rb.y);

    printf("%d %d %d %d\n", a.lt.x, a.lt.y, a.rb.x, a.rb.y);
    printf("%d %d %d %d\n", b.lt.x, b.lt.y, b.rb.x, b.rb.y);

    if (is_crossed(a, b)) {
        struct Rect c = intersection(a, b);
        printf("%d %d %d %d\n", c.lt.x, c.lt.y, c.rb.x, c.rb.y);
    }

    return 0;
}


int is_crossed(struct Rect a, struct Rect b) {
    if ((a.lt.x <= b.rb.x) && (b.lt.x <= a.rb.x) && (a.lt.y >= b.rb.y) && (b.lt.y >= a.rb.y)) {
        return 1;
    } else {
        return 0;
    }
}

struct Rect intersection(struct Rect a, struct Rect b) {
    if (!is_crossed(a, b)) {
        return ((struct Rect){});
    }

    struct Rect res;
    res.lt.x = (a.lt.x >= b.lt.x ? a.lt.x : b.lt.x);
    res.lt.y = (a.lt.y <= b.lt.y ? a.lt.y : b.lt.y);
    res.rb.x = (a.rb.x <= b.rb.x ? a.rb.x : b.rb.x);
    res.rb.y = (a.rb.y >= b.rb.y ? a.rb.y : b.rb.y);

    return res;
}