#include <stdio.h>

void simpleFactors(unsigned int a, unsigned int last, unsigned int n);

void printFactor(unsigned int last, unsigned int n);

int main(){
    unsigned int a;
    scanf("%u", &a);
    simpleFactors(a, 2, 0);
    printf("\n");
    return 0;
}

void printFactor(unsigned int last, unsigned int n){
    if (n == 1) {
        printf("%u ", last);
    } else if (n > 1) {
        printf("%u^%u ", last, n);
    }
}

void simpleFactors(unsigned int a, unsigned int last, unsigned int n){
    //printf("meaning of simpleFactors(%u, %u, %u)\n", a, last, n);
    if (a <= 1) {
        if (n > 0) {
            printFactor(last, n);
        }
        return;
    }


    if (a % last == 0) {
        simpleFactors(a / last, last, n + 1);
    } else {

        if (last == 2) {
            simpleFactors(a, last + 1, 0);
        } else {
            simpleFactors(a, last + 2, 0);
        }
        if (n > 0) {
            printFactor(last, n);
        }
    }
    //printf("meaning of simpleFactors(%u, %u, %u)\n", a, last, n);
}