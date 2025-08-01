#include <stdio.h>

typedef struct
{
    int yy; // год
    char mm; // месяц
    char dd; // день
}Data;

typedef struct
{
    int yy; // год
    char season; // время года (зима - 0, весна - 1, лето - 2, осень - 3)
    int day; // день от начала текущего времени года
}Season;

Data getData(); // получает параметры даты с консоли
void printData(Data); // Печатает дату в формате: YYYY-MM-DD
Season convToSeas(Data); // конвертирует дату в формат Season
void printSeas(Season); //  печать времени года в формате: YYYY-SS-DD

int main()
{
    Data dat;
    Season seas;
    dat = getData();
    printData(dat);
    seas = convToSeas(dat);
    printSeas(seas);

    return 0;
}

Data getData() {
    Data f;
    scanf("%d-%hhd-%hhd", &f.yy, &f.mm, &f.dd);
    return f;
}

void printData(Data p) {
    printf("%04d-%02d-%02d\n", p.yy, p.mm, p.dd);
}

Season convToSeas(Data p) {
    Season f;

    if ((p.mm >= 1  && p.mm <= 2) || (p.mm == 12)) {
        f.season = 0;
        if (p.mm == 12) {
            f.day = p.dd;
        }
        if(p.mm == 1) {
            f.day = p.dd + 31;
        }
        if(p.mm == 2) {
            f.day = p.dd + 31 * 2;
            /*
            if ((p.yy % 4 == 0 && p.yy % 100 != 0) || (p.yy % 400 == 0)) {
                p.dd <= 29;
                f.day = p.dd + 31 * 2;
            } else {

            }
            */
        }
    } else if (p.mm >= 3 && p.mm <= 5) {
        f.season = 1;
        if (p.mm == 3) {
            f.day = p.dd;
        }
        if (p.mm == 4) {
            f.day = p.dd + 31;
        }
        if (p.mm == 5) {
            f.day = p.dd + 31 + 30;
        }
    } else if (p.mm >= 6 && p.mm <= 8) {
        f.season = 2;
        if (p.mm == 6) {
            f.day = p.dd;
        }
        if (p.mm == 7) {
            f.day = p.dd + 30;
        }
        if (p.mm == 8) {
            f.day = p.dd + 30 + 31;
        }
    } else if (p.mm >= 9 && p.mm <= 11) {
        f.season = 3;
        if (p.mm == 9) {
            f.day = p.dd;
        }
        if (p.mm == 10) {
            f.day = p.dd + 30;
        }
        if (p.mm == 11) {
            f.day = p.dd + 30 + 31;
        }
    }

    f.yy = p.yy;

    return f;
}

void printSeas(Season f) {
    printf("%04d-%02d-%02d\n", f.yy, f.season, f.day);
}