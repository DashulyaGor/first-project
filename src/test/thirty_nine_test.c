#include <stdio.h>
#include <stdlib.h>


void center(int xlt, int ylt, int xrb, int yrb, int *pxc, int *pyc);
void rotateC(int *x1, int *y1, int *x2, int *y2);

int main(){
    int xlt, ylt, xrb, yrb;

    scanf("%d%d%d%d", &xlt, &ylt, &xrb, &yrb);

    rotateC(&xlt, &ylt, &xrb, &yrb);

    printf("%d %d %d %d\n", xlt, ylt, xrb, yrb);

    return 0;
}

void center(int xlt, int ylt, int xrb, int yrb, int *pxc, int *pyc){
    *pxc = (xlt + xrb) / 2;
    *pyc = (ylt + yrb) / 2;
}


void rotateC(int *x1, int *y1, int *x2, int *y2){
    int pxc, pyc, hw, hh;

    center(*x1, *y1, *x2, *y2, &pxc, &pyc);

    hw = (*x2 - *x1) / 2;
    hh = (*y2 - *y1) / 2;

    *x1 = pxc + hh;
    *y1 = pyc + hw;
    *x2 = pxc - hh;
    *y2 = pyc - hw;
}