#include <stdio.h>


#define LEN ('z' - 'a' + 1)
#define START ('a' % LEN)


// возвращает букву letter, закодированную шифром Цезаря со сдвигом shift
int code(int letter, int shift)
{
    return 'a' + (letter - START + (shift % LEN)) % LEN;
}


int main()
{
    // читаем по символу
    char c1, c2, c3, c4;    // ASCII-коды символов
    int shift;              // сдвиг шифра Цезаря


    // читаем символы и сдвиг
    scanf("%c%c%c%c", &c1, &c2, &c3, &c4);
    scanf("%d", &shift);


    // кодируем символы
    c1 = code(c1, shift);
    c2 = code(c2, shift);
    c3 = code(c3, shift);
    c4 = code(c4, shift);


    // печатаем символы
    printf("%c%c%c%c\n", c1, c2, c3, c4);


    return 0;
}