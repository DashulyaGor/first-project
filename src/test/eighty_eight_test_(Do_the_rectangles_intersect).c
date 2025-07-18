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


int main() {
    struct Rect a, b;
    int intersection;

    scanf("%d%d%d%d", &a.lt.x, &a.lt.y, &a.rb.x, &a.rb.y);
    scanf("%d%d%d%d", &b.lt.x, &b.lt.y, &b.rb.x, &b.rb.y);

    intersection = is_crossed(a, b);

    printf("%d %d %d %d\n", a.lt.x, a.lt.y, a.rb.x, a.rb.y);
    printf("%d %d %d %d\n", b.lt.x, b.lt.y, b.rb.x, b.rb.y);
    printf("%d\n", intersection);
    
    return 0;
}


int is_crossed(struct Rect a, struct Rect b) {
    if ((a.lt.x <= b.rb.x) && (b.lt.x <= a.rb.x) && (a.lt.y >= b.rb.y) && (b.lt.y >= a.rb.y)) {
        return 1;
    } else {
        return 0;
    }
}