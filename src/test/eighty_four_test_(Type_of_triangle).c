#include <stdio.h>

int triangle_len_type(int a, int b, int c);

int main()
{
    int a, b, c, res;
    scanf("%d%d%d", &a, &b, &c);
    res = triangle_len_type(a, b, c);
    printf("%d\n", res);
    return 0;
}

int triangle_len_type(int a, int b, int c) {
    int n;
    if (a >= (b + c) || b >= (a + c) || c >= (a + b)) {
        return -1;
    }
    if ((a == b) || (b == c) || (a == c)) {
        n = 1;
    }
    if ((a != b) && (b != c) && (a != c)) {
        n = 0;
    }
    if ((a == b) && (b == c) && (a == c)) {
        n = 2;
    }

    return n;
}