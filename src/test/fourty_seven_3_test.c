#include <stdio.h>

void run(unsigned int cur, unsigned int n);

int main(){
    unsigned int a, n;
    scanf("%u%u", &a, &n);
    run(a, n);
    return 0;
}


void run(unsigned int cur, unsigned int n) {
    printf("(%u %u)", cur, n);
    if (cur < n) {
        run(cur + 1, n);
    }
    printf("%u\n", cur);

}