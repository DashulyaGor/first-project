#include <stdio.h>

void center(int xlt, int ylt, int xrb, int yrb, int *pxc, int *pyc);

int main(){
    int xlt, ylt, xrb, yrb, x, y;

    scanf("%d%d%d%d", &xlt, &ylt, &xrb, &yrb);

    center(xlt, ylt, xrb, yrb, &x, &y);

    printf("%d %d\n", x, y);

    return 0;
}

void center(int xlt, int ylt, int xrb, int yrb, int *pxc, int *pyc){
    *pxc = (xlt + xrb) / 2;
    *pyc = (ylt + yrb) / 2;
}