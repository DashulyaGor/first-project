#include <stdio.h>

int main() {
    int x;
    scanf("%d", &x);

    // Номиналы монет в порядке убывания
    int coins[] = {5000, 1000, 500, 100, 50, 10, 5, 2, 1};
    int num_coins = 9;

    // Для каждого номинала подсчитываем количество монет
    for (int i = 0; i < num_coins; i++) {
        int denomination = coins[i];
        int count = x / denomination;
        if (count > 0 || 1) {  // Всегда выводим
            printf("%d %d\n", denomination, count);
            x -= denomination * count;
        }
    }

    return 0;
}