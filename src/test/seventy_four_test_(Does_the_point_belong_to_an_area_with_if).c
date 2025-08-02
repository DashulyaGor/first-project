#include <stdio.h>

typedef struct {
    float x;
    float y;
} Point;

int main() {
    Point b;
    scanf("%f%f", &b.x, &b.y);

    if (b.x >= -3 && b.x <= 2 && b.y >= -4 && b.y <= 6) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}