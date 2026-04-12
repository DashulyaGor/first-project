#include <stdio.h>

#define ROWS 3
#define COLUMNS 3

int sum(int a[ROWS][COLUMNS])
{
    int sum = 0;
    for(int j = 0; j < COLUMNS; j++) {
        sum += a[1][j];
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
    
    printf("%d\n", sum(a));

    return 0;
}