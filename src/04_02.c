#include <stdio.h>

int main() {
    int n, max = 0, flag = 1;

    while(n != -1) {
        if(scanf("%d", &n) == 1 && n >= -1) {
            if(n > max) {
            max = n;
        }
    } else {
        flag = 0;
        break;
    }
}

if(flag == 1) {
    printf("%d", max);
} else {
    printf("n/a");
}
return 0;
}