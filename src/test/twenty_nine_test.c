#include <stdio.h>

void print_revers(int x);

int main(){
    int x;

    scanf("%d", &x);

    print_revers(x);

    return 0;
}

void print_revers(int x){
    int first, second, third, fourth, fifth, sixth;

    sixth = x % 10;
    x = (x - sixth) / 10;
    fifth = x % 10;
    x = (x - fifth) / 10;
    fourth = x % 10;
    x = (x - fourth) / 10;
    third = x % 10;
    x = (x - third) / 10;
    second = x % 10;
    x = (x - second) / 10;
    first = x % 10;
    printf("%d%d%d%d%d%d\n", sixth, fifth, fourth, third, second, first);
}