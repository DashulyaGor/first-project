#include <stdio.h>
//#include <assert.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

void printPoint(Point p) {
    printf("(%d,%d) ", p.x, p.y);
}

Point readPoint() {
    Point res;
    scanf("%d%d", &res.x, &res.y);
    return res;
}

void scanPoint(Point *p) {
    scanf("%d%d", &p->x, &p->y);
}

Point movePoint1(Point p, int dx) {
    Point res = p;
    res.x += dx;
    return res;
}

void movePoint2(Point *p, int dx) {
    p->x += dx;
}

float distance(Point p1, Point p2) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

/*
int is_equal(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}
*/
int main() {
    Point p1, p2;
    p1 = readPoint();
    scanPoint(&p2);

    printPoint(p1);
    printPoint(p2);

    float d = distance(p1, p2);
    printf("%.02f ", d);
    //assert(d == 10);

    Point p_new = movePoint1(p1, 2);
    printPoint(p_new);
    Point exp_point = p_new;
    d = distance(p_new, p2);
    printf("%.02f ", d);
    //assert(is_equal(exp_point, p_new));

    exp_point.x += 2;
    movePoint2(&p_new, 2);
    printPoint(p_new);
    d = distance(exp_point, p2);
    printf("%.02f ", d);
    //assert(is_equal(exp_point, p_new));

    printf("\n");

    return 0;
}