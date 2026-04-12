#include <stdio.h>

#define ROWS 3
#define COLUMNS 3

int main()
{
    int a[ROWS][COLUMNS];
    int sum = 0;

    // чтение массива
    for(int i = 0; i < ROWS; i++) {
        // чтение одной строки a[i]
        for(int j = 0; j < COLUMNS; j++) {
            scanf("%d", &a[i][j]);
            sum += a[i][j];
        }
    }
    
    printf("%d\n", sum);

    return 0;
}