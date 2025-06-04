#include <stdio.h>

void min2time(int mm, int *ph, int *pm);

int main()
{
    int mm, h, m;
    scanf("%d", &mm);

    min2time(mm, &h, &m);// напишите вызов функции min2time

    printf("%02d:%02d\n", h, m);

    return 0;
}

void min2time(int mm, int *ph, int *pm){

    *ph = mm / 60;
    if(*ph > 24){
        (*ph) -= 24;
    } else if(*ph == 24){
        *ph = 00;
    }
    *pm = mm % 60;
}