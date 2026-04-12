#include <stdio.h>

#define ROWS 3
#define COLUMNS 3

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

    a[1][2] *= 10;


    // печать массива
    for(int i = 0; i < ROWS; i++) {
        // печать одной строки a[i]
        for(int j = 0; j < COLUMNS; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}