#include <stdio.h>

int main() {
    int height;
    int total_students = 0;
    int tall_students = 0;

    while (scanf("%d", &height) == 1) {
        total_students++;
        if (height > 170) {
            tall_students++;
        }
    }

    printf("%d %d\n", total_students, tall_students);

    return 0;
}