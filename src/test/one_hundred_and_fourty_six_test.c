#include <stdio.h>

int main () {
    char a[101];
    int n; //количество строк
    int count = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%100s", a);

        for (int j = 0; a[j] != '\0'; j++) {
            if(a[j] == '*') {
            count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}