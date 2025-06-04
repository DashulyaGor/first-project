#include <stdio.h>
#include <assert.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point a;
    Point b;
} Line;


void printPoint(Point p) {
    printf("(%d,%d) ", p.x, p.y);
}

void printLine(Line s) {
    printf("(%d,%d) (%d,%d) \n", s.a.x, s.a.y, s.b.x, s.b.y);
}

/*
void printLine(Line s) {
    printPoint(s.a);
    printPoint(s.b);
    printf("\n");
}
*/

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

float lenght(Line p1) {
    return distance(p1.a, p1.b);
}


int is_equal(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

int is_equalLine(Line p1, Line p2) {
    return is_equal(p1.a, p2.a) && is_equal(p1.b, p2.b);
}

Line moveLine1(Line s, int dx) {
    Line res;
    res.a = movePoint1(s.a, dx);
    res.b = movePoint1(s.b, dx);
    return res;
}

void moveLine2(Line *p, int dx) {
    movePoint2(&p->a, dx);
    movePoint2(&p->b, dx);
}

int main() {
    Point p1, p2;
    p1 = readPoint();
    scanPoint(&p2);

    printPoint(p1);
    printPoint(p2);

    float d = distance(p1, p2);
    printf("%.02f ", d);
    assert(d == 10);

    Line s = {{2, 3}, {5, 7}};
    printLine(s);
    printf("length=%.2f\n", lenght(s));
    assert(lenght(s) == 5);

    Point p_new = movePoint1(p1, 2);
    printPoint(p_new);
    Point exp_point = p_new;
    d = distance(p_new, p2);
    printf("%.02f ", d);
    assert(is_equal(exp_point, p_new));
    Line s_new = moveLine1(s, 3);
    printLine(s_new);
    Line exp_line = {{5, 3}, {8, 7}};
    assert(is_equalLine(s_new, exp_line));

    exp_point.x += 2;
    movePoint2(&p_new, 2);
    printPoint(p_new);
    d = distance(exp_point, p2);
    printf("%.02f ", d);
    assert(is_equal(exp_point, p_new));
    exp_line.a.x += 3;
    exp_line.b.x += 3;
    moveLine2(&s_new, 3);
    printLine(s_new);
    assert(is_equalLine(s_new, exp_line));

    printf("\n");

    return 0;
}