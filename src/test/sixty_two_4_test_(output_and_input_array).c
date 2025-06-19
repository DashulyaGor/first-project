#include <stdio.h>

int read_int() {
    int num;
    scanf("%d", &num);
    return num;
}

int main(){
    const int SIZE = 6;
    int arr [SIZE];

    for(int i = 0; i < SIZE; ++i) {
        printf("Input %d-th number ", i + 1);
        arr[i] = read_int();
    }

    printf("\nArray:\n");
    for(int i = 0; i < SIZE; ++i) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return 0;
}