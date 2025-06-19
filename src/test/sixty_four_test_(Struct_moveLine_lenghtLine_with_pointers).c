#include <stdio.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point a;
    Point b;
    float len;
} Line;


void scanPoint(Point *p);
void scanLine(Line *t);
void movePoint2(Point *t);
void rotRLine(Line *t);
float distance(Line t);
float lenght(Line p1);
void printLine(Line s);


int main() {

Line t;
scanLine (&t);
rotRLine(&t);
printLine(t);

return 0;
}

void scanPoint(Point *t) {
    scanf("%d%d", &t->x, &t->y);
}

void scanLine(Line *t) {
    scanPoint(&t->a);
    scanPoint(&t->b);
}

void movePoint2(Point *t) {
    int temp_y = t->y;
    t->y = -t->x;
    t->x = temp_y;
}

void rotRLine(Line *t) {
    movePoint2(&t->a);
    movePoint2(&t->b);
}

float distance(Line t) {
    int tx = t.a.x - t.b.x;
    int ty = t.a.y - t.b.y;
    t.len = sqrt(tx * tx + ty * ty);
    return t.len;
}

float lenght(Line t) {
    return distance(t);
}

void printLine(Line t) {
    printf("%d %d %d %d %.3f\n", t.a.x, t.a.y, t.b.x, t.b.y, lenght(t));
}