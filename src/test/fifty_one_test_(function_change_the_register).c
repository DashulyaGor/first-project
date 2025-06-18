#include <stdio.h>
#include <ctype.h>

int main(){
    char c;
    char res;

    scanf("%c", &c);

    res = tolower(c);

    printf("%c\n", res);

    return 0;
}