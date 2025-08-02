#include <stdio.h>

typedef struct {
    float x;
    float y;
} Point;

int main() {
    Point b;
    scanf("%f%f", &b.x, &b.y);

    if (b.y <= 3 + b.x && b.y <= 3 - b.x && b.y >= -2) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}