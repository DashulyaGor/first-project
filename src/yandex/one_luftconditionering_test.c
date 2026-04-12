#include <stdio.h>
#include <string.h>

int main() {
    int troom, tcond;
    char mode[10];

    // Считываем текущую и желаемую температуру
    scanf("%d %d", &troom, &tcond);

    // Считываем режим работы
    scanf("%s", mode);

    int result;

    if (strcmp(mode, "freeze") == 0) {
        // Охлаждение: уменьшаем до tcond, если нужно
        result = (troom <= tcond) ? troom : tcond;
    }
    else if (strcmp(mode, "heat") == 0) {
        // Нагрев: увеличиваем до tcond, если нужно
        result = (troom >= tcond) ? troom : tcond;
    }
    else if (strcmp(mode, "auto") == 0) {
        // Авто: устанавливаем точно tcond
        result = tcond;
    }
    else if (strcmp(mode, "fan") == 0) {
        // Вентиляция: ничего не меняем
        result = troom;
    }
    else {
        // На случай неизвестного режима
        result = troom;
    }

    printf("%d\n", result);

    return 0;
}