#include <stdio.h>

int equivalent(int a, int b) {
    return a == b ? 1 : 0;
}

int main() {
    for (int A = 0; A <= 1; ++A) {
        for (int B = 0; B <= 1; ++B) {
            int left_side = ((A && B) || (!A && !B));
            int right_side = equivalent(A, B);

            printf("For A = %d, B = %d: left side = %d, right side = %d\n", A, B, left_side, right_side);

            if (left_side != right_side) {
                printf("The identity is incorrect!\n");
                return 1;
            }
        }
    }
    printf("The identity is correct!\n");
    return 0;
}