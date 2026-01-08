#include <stdio.h>

int all_equal(int n, int coins[]) {
    for (int i = 1; i < n; i++) {
        if (coins[i] != coins[0]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    int coins[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    int merchant_coins = 0;

    while (!all_equal(n, coins)) {
        //Обработка пар по кругу: (0, 1), (1, 2), ..., (n - 1, 0)
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n; //Следующий элемент после i
            int sum = coins[i] + coins[j];

            if (sum % 2 == 1) {
                merchant_coins++;
            }

            //Делим сумму на 2
            int each = sum / 2;
            coins[i] = each;
            coins[j] = each;
        }
    }

    printf ("%d %d\n", merchant_coins, coins[0]);
    return 0;
}