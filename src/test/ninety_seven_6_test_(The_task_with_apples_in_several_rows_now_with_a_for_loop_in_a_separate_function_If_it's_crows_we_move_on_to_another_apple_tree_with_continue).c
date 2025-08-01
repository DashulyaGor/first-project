#include <stdio.h>

int main() {
    
    int rows;
    int j;
    int total;

    int x;
    int sum;
    int n;
    int i;

    scanf("%d", &rows);

    total = 0;
    for (j = 0; j < rows; j++) {
        scanf("%d", &n);
        sum = 0;

        for (i = 0; i < n; i++) {
            scanf("%d", &x);
            if (x < 0) {
                printf ("Вороны!\n");
                continue;
            }
            sum += x;
            printf ("j = %d i = %d x = %d sum = %d\n", j, i, x, sum);
        }
        total += sum;
        printf ("j = %d total = %d\n", j, total);
    }
    printf("%d\n", total);
    return 0;
}