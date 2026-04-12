#include <stdio.h>

#define DBG_PRN(format, x) printf(#x " = " format "\n", x)


int main() {
    int a = 56;
    double x = 3.14;
    char *str = "Hello";
    
    DBG_PRN("%.1f", x);        // Вывод: x = 3.1
    DBG_PRN("%d", a);      // Вывод: a = 56
    DBG_PRN("%s", str);      // Вывод: str = Hello
    
    return 0;
}