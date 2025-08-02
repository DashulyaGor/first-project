#include <stdio.h>

int main(){
    int y = 123;
    int* p = &y;
    printf("p = %p\n", p);
    return 0;
}