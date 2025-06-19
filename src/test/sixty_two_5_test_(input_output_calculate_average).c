#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

void scan_int(int* ptr) {
    scanf("%d", ptr);
}

double calculate_average(const int* array, size_t size) {
    long long sum = 0LL;
    for (size_t i = 0; i < size; ++i) {
        sum += array[i];
    }
    return ((double)sum / size);
}

int main() {
    int data[ARRAY_SIZE];
    size_t count = 0;

    while (count < ARRAY_SIZE) {
        int temp;
        if (scanf("%d", &temp) == EOF) break;

        scan_int(&data[count]);
        count++;
    }

    if (count > 0) {
        double average = calculate_average(data, count);
        printf("Arithmetic mean: %.2lf\n", average);
    } else {
        printf("error: data is not entered.\n");
    }

    return 0;
}