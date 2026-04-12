#include <stdio.h>

#define ROWS 3
#define COLUMNS 3

int sum_diag(int a[ROWS][COLUMNS])
{
    int sum = 0;
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLUMNS; j++) {
            if (i == j) {
                sum += a[i][j];
            }
        }
    }
    
    return sum;
}
int main()
{
    int a[ROWS][COLUMNS];


    // чтение массива
    for(int i = 0; i < ROWS; i++) {
        // чтение одной строки a[i]
        for(int j = 0; j < COLUMNS; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    printf("%d\n", sum_diag(a));

    return 0;
}