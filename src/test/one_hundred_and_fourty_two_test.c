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

    int target_sum = 0;
    for(int j = 0; j < COLUMNS; j++) {
        target_sum += a[0][j];
    }

    
    for(int i = 1; i < ROWS; i++) {
        int row_sum = 0;
        for(int j = 0; j < COLUMNS; j++) {
            row_sum += a[i][j];
        }
        if (row_sum != target_sum) {
            printf("NO\n");
            return 0;
        }
    }

    for(int j = 1; j < COLUMNS; j++) {
        int col_sum = 0;
        for(int i = 0; i < ROWS; i++) {
            col_sum += a[i][j];
        }
        if (col_sum != target_sum) {
            printf("NO\n");
            return 0;
        }
    }

    int diag_sum = 0;
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLUMNS; j++) {
            if (i == j) {
                diag_sum += a[i][j];
            }
        }
    }
    if (diag_sum != target_sum) {
        printf("NO\n");
        return 0;
    }

    int diag2_sum = 0;
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLUMNS; j++) {
            if (i + j == ROWS - 1) { // условие для побочной диагонали
                diag2_sum += a[i][j];
            }
        }
    }
    if (diag2_sum != target_sum) {
        printf("NO\n");
        return 0;
    }
    //Если все совпало
    printf("MAGIC\n");

    return 0;
}