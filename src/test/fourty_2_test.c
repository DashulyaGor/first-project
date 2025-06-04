#include <stdio.h>


void foo() {
    static int x;  // неявная инициализация
    x = x + 1;
    printf("%d ", x);
}


int main() {
    foo();
    foo();
    return 0;
}