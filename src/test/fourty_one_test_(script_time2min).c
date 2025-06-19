#include <stdio.h>

#define time2min(h,m) ((h) * 60 + (m))


int main(){
    int h, m, mm;
    scanf("%d:%d", &h, &m);

    mm = time2min(h, m);
    printf("%d\n", mm);

    mm = time2min(h, m)*2;
    printf("%d\n", mm);

    mm = time2min(h+1, m+5);
    printf("%d\n", mm);
    return 0;
}