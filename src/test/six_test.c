#include <stdio.h>

int main(){
    int h, m, sec;// объявить переменные
    
    scanf("%d%d", &h, &m); // прочитать входные данные

    m = h * 60 + m; // вычислить
    sec = m * 60;
    
    printf("%d\n%d\n", m, sec);// напечатать результат

    return 0;
}