#include <stdio.h>


// объявили новый тип данных struct Segment
// 1D отрезок
struct Segment {
    int start;    // один конец отрезка
    int finish;   // другой конец отрезка
};


int main() {
    struct Segment a = {-4, 7}, b;
    b.start = 6;
    b.finish = 0;


                            // распечатаем эти отрезки:
    printf("a = [%d, %d]\n", a.start, a.finish);
    printf("b = [%d, %d]\n", b.start, b.finish);


    struct Segment m;
    scanf("%d", &m.start);  // читаем
    scanf("%d", &m.finish);
                            // печатаем
    printf("m = [%d, %d]\n", m.start, m.finish);


    return 0;
}