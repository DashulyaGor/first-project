#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n % 100 >= 11 && n % 100 <= 14) {
        printf("%d коров\n", n);
    } else {
        switch (n % 10) {
            case 1:
            printf("%d корова\n", n);
            break;
            case 2:
            case 3:
            case 4:
            printf("%d коровы\n", n);
            break;
            default:
            printf("%d коров\n", n);
        }
    }

    return 0;
}