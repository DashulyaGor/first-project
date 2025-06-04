#include <stdio.h>

int nod(int a, int b);

int main(){
    int x, y, res;

    scanf("%d%d", &x, &y);

    res = nod(x, y);

    printf("%d\n", res);
    return 0;
}

int nod(int a, int b){
    int res;
    if (b == 0) {
        return a;
    } else {
        res = nod(b, a % b);
    }
    return res;
}