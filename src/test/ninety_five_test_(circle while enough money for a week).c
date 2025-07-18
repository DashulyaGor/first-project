#include <stdio.h>

int main() {
    int price;
    int new_price;
    int delta;
    int money; //всего денег
    int wday; //день недели

    int i; //закончился день

    scanf("%d%d%d", &price, &delta, &money);

    new_price = price;
    i = 0;
    wday = 1;

    while (money >= new_price) {
        money -= new_price;
        i++;
        wday++;

        if (wday > 7) {
            wday = 1;
            new_price += delta;
        }
    }

    printf("%d\n", i);

return 0;
}