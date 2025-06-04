#include <stdio.h>

int read_int();
void scan_int();

int read_int()
{
    int res;
    scanf("%d", &res);
    return res;
}
void scan_int(int * p)
{
    scanf("%d", p);     // p уже указатель, не нужно &
}
int main()
{
    int x, y;
    x = read_int();
    scan_int(&y);
    printf("x=%d y=%d\n", x, y);


    return 0;
}