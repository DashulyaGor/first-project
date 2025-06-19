#include <stdio.h>
#include <math.h>

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Color;

Color getColor();
unsigned long long convertToHTML(Color x);
Color convertToRGB(unsigned long long);
void printRGB(Color f);
void printHTML(Color f);

int main(){
    Color z, z2;
    unsigned long long html;

    z = getColor();
    printRGB(z);

    html = convertToHTML(z);
    printf("%llu\n", html);
    printHTML(z);

    z2 = convertToRGB(html);
    printRGB(z2);

    return 0;
}

Color getColor() {
    Color f;
    scanf("%hhd%hhd%hhd", &f.red, &f.green, &f.blue);
    return f;
}

unsigned long long convertToHTML(Color x) {
    unsigned long long res;
    res = x.red * pow(256, 2) + x.green * pow(256, 1) + x.blue * pow(256, 0);
    return res;
}

Color convertToRGB(unsigned long long x) {
    Color f;
    f.red = x / pow(256, 2);
    f.green = x / pow(256, 1);
    f.blue = x;
    return f;
}

void printRGB(Color f) {
    printf("%d %d %d\n", f.red, f.green, f.blue);
}

void printHTML(Color f) {
    printf("%02X%02X%02X\n", f.red, f.green, f.blue);
}