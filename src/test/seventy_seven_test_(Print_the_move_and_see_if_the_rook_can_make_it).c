#include <stdio.h>

typedef struct {
    char x;
    int y;
} Point;


int main() {
    Point f, g;
    
    scanf("%c%d-%c%d", &f.x, &f.y, &g.x, &g.y);
    printf("%c%d-%c%d\n", f.x, f.y, g.x, g.y);

    if ((f.x >= 'a' && f.x <= 'h') || (f.y >= 1 && f.y <= 8) || (g.x >= 'a' && g.x <= 'h') || (g.y >= 1 && g.y <= 8)) {
        if (f.x == g.x || f.y == g.y) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}