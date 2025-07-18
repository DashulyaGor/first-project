#include <stdio.h>

int main() {
    int n; //Total sticks
    int k; //Winning first move number of sticks
    int pl1 = 1; //first player
    int pl2 = 1; //second player
    int res;

    scanf("%d", &n);

    res = n - pl1;
    n = res;
    

    if (res != 1 && pl1 <= 3) {
        pl1++;
        res = n - pl1;
    } else {
        k = pl1;
        printf("%d = %d - %d\n", res, n, k);
    }
    
    res = n - pl2;
    if (res != 1 && pl2 <= 3) {
        pl2++;
        res = n - pl2;
    } else {
        printf("%d = %d - %d\n", res, n, pl2);
        n = res;
    }

    if (res != 1 && pl1 <= 3) {
        pl1++;
        res = n - pl1;
    } else {
        k = pl1;
        printf("%d = %d - %d\n", res, n, k);
    }

    if (res != 1 && pl2 <= 3) {
        pl1++;
        res = n - pl2;
    } else {
        printf("%d = %d - %d\n", res, n, pl2);
        n = res;
    }


    } else {
        printf("-1\n");
    }

    return 0;
}