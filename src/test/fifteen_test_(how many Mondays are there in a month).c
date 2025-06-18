#include <stdio.h>

int main(){
    int n, day;

    scanf("%d%d", &n, &day);

    int res = ((n - day) / 7) + 1;

    printf("%d\n", res);

    return 0;
}