#include <stdio.h>

void sort2(int *x, int *y);
void sort3(int *a, int *b, int *c, int *w, int *h);

int main()
{
    int a, b, x, y, z;
    scanf("%d%d", &a, &b);
    scanf("%d%d%d", &x, &y, &z);
    sort3(&x, &y, &z, &a, &b);
    //printf("%d %d %d\n", x, y, z);
    return 0;
}

void sort2(int *x, int *y) {
    if (*x > *y) {
        int k = *x;
        *x = *y;
        *y = k;
    }
}

void sort3(int *a, int *b, int *c, int *w, int *h) {
    if (*a > *b || *a > *c || *b > *c) {
        sort2(a, b);
        sort2(a, c);
        sort2(b, c);
    }
    if (*w > *h) {
        sort2(w, h);
    }
    if (*w >= *a && *h >= *b) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}