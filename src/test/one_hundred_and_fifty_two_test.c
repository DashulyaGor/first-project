#include <stdio.h>
#include <string.h>

char *my_strcat(char *dest, const char *src);

int main() {
char str1[100];
char str2[100];

scanf("%s", str1);
scanf("%s", str2);

my_strcat(str1, str2);

printf("%s\n", str1);

return 0;
}

char *my_strcat(char *dest, const char *src) {
    strcpy(dest + strlen(dest), src);
    return dest;
}