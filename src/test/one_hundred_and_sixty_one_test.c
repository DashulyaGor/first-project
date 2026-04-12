#include <stdio.h>

int main() {
    int c,          //цвет текущего шара
        c0 = 0,     //счетчик для цвета 0 (красный)
        c1 = 0,     //счетчик для цвета 1 (желтый)
        c2 = 0,     //счетчик для цвета 2 (зеленый)
        c3 = 0;     //счетчик для цвета 3 (синий)

        //читаем и считаем шары
        while(scanf("%d", &c) == 1) {
            switch(c) {
                case 0: c0++; break;
                case 1: c1++; break;
                case 2: c2++; break;
                case 3: c3++; break;
                default: printf("Error: unknown color %d\n", c); break;
            }
        }

        //печатаем результат
        printf("0 %d\n", c0);
        printf("1 %d\n", c1);
        printf("2 %d\n", c2);
        printf("3 %d\n", c3);

        return 0;
}