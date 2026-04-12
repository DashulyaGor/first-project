#include <stdio.h>

#define N 100

int main () {
    char square[N][N];
    char a[101];
    int n; //количество строк
    int area = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%100s", a);

        for (int j = 0; a[j] != '\0'; j++) {
            square[i][j] = a[j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (square[i][j] == '*') {
                if ((i == 0 || square[i-1][j] == '.') && (j == 0 || square[i][j-1] == '.')) {
                    int i_end = i;
                    int j_end = j;

                    while (i_end < n && square[i_end][j] == '*') {
                        int temp_j = j;
                        while (temp_j < n && square[i_end][temp_j] == '*') {
                            temp_j++;
                        }

                        j_end = temp_j - 1;
                        i_end++;
                    }
                    i_end--;

                    int length = i_end - i + 1;
                    int width = j_end - j + 1;
                    int temp_area = length * width;

                    if (temp_area > area) {
                        area = temp_area;
                    }
                }
            }
        }
    }
    
    printf("%d\n", area);
    return 0;
}