#include <stdio.h>
#include <stdlib.h>

int getNumbers(int *number, int n);

int main() {
    int n;
    scanf("%d", &n);

    int *A = (int*)malloc(n*sizeof(int));
    int *B = (int*)malloc(n*sizeof(int));

    if (A != NULL && B != NULL) {
        printf("Ошибка выделения  памяти.\n");
        free(A);
        free(B);
        return 1;
    }
    
    if (getNumbers(A, n) && getNumbers(B, n)) {
        printf("Ошибка ввода.\n");
        free(A);
        free(B);
        return 1;
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        result += A[i] * B[i];
    }
    
    printf("%d\n", result);

    free(A);
    free(B);

    return 0;
        
}
    

int getNumbers(int *number, int n) {
    char c;
    int flag = 1;

    for (int i = 0; i < n; i++) {
        if (scanf("%d%c", &number[i], &c) == 2) {
            if (i != n - 1) {
                if (c != ' ') {
                    flag = 0;
                    break;
                }
            } else {
                if (c != '\n' && c != EOF) {
                    flag = 0;
                    break;
                }
            }
        } else {
            flag = 0;

            break;
        }
    }
    return flag;
}