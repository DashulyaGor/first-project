#include <stdio.h>

void move(int *px, int *py, int dx, int dy);

int main(){
    int x, y, dx, dy;

    scanf("%d%d%d%d", &x, &y, &dx, &dy);

    move(&x, &y, dx, dy);

    printf("%d %d\n", x, y);

    return 0;
}

void move(int *px, int *py, int dx, int dy){
    *px = *px + dx;
    *py = *py + dy;
}