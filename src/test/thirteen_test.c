#include <stdio.h>

int main(){
    float S, w, ch;

    scanf("%f%f%f", &S, &w, &ch);

    int res = S / w / ch;

    printf("%d\n", res);

    return 0;
}