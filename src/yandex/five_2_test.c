#include <stdio.h>

int main() {
    long long K1, M, K2, P2, N2;
    scanf("%lld %lld %lld %lld %lld", &K1, &M, &K2, &P2, &N2);

    const long long MAX_VAL = 1000000;

    // Проверка: все положительные и <= 10^6
    if (K1 <= 0 || M <= 0 || K2 <= 0 || P2 <= 0 || N2 <= 0) {
        printf("-1 -1\n");
        return 0;
    }
    if (K1 > MAX_VAL || K2 > MAX_VAL || P2 > MAX_VAL || N2 > MAX_VAL || M > MAX_VAL) {
        printf("-1 -1\n");
        return 0;
    }
    if (N2 > M) {
        printf("-1 -1\n");
        return 0;
    }

    // Массив возможных x
    long long possible_x[100000];
    int count = 0;

    long long L_val = (P2 - 1) * M + N2 - 1;  // коэффициент перед x в левой части
    long long R_val = (P2 - 1) * M + N2;

    if (L_val == 0) {
        if (K2 >= 1) {
            possible_x[count++] = K2;
        }
        if (MAX_VAL >= 1) {
            possible_x[count++] = (K2 < MAX_VAL) ? MAX_VAL : K2 * 2;
        }
        if (K2 < MAX_VAL) {
            possible_x[count++] = MAX_VAL;
        } else {
            possible_x[count++] = K2 * 2;
        }
        // добавить min_x и большое значение
    } else {
        long long max_x = (K2 - 1) / L_val;
        long long min_x = (K2 + R_val - 1) / R_val;  // из K2 <= x * R_val
        if (min_x < 1) min_x = 1;
        if (max_x > 2000000) max_x = 2000000;
        if (min_x > max_x) {
            printf("-1 -1\n");
            return 0;
        } else{

            for (long long x = min_x; x <= max_x; x++) {
                long long base = (P2 - 1) * M * x;
                long long start_floor = base + (N2 - 1) * x + 1;
                long long end_floor = base + N2 * x;

                if (K2 >= start_floor && K2 <= end_floor) {
                    possible_x[count++] = x;
                }
            }
        }
    }

    if (count == 0) {
        printf("-1 -1\n");
        return 0;
    }

    // Вычисляем все возможные (P1, N1)
    long long p1_values[1000], n1_values[1000];
    int total = 0;

    for (int i = 0; i < count; i++) {
        long long x = possible_x[i];

        if (x < 1) continue;
        if (M < 1) continue;

        long long apart_per_entrance = M * x;

        if (apart_per_entrance == 0) continue;

        long long p1 = (K1 - 1) / apart_per_entrance + 1;
        long long pos_in_entrance = (K1 - 1) % apart_per_entrance;
        long long n1 = pos_in_entrance / x + 1;

        if (p1 <= 0 || n1 <= 0 || n1 > M) continue;

        p1_values[total] = p1;
        n1_values[total] = n1;
        total++;
    }

    if (total == 0) {
        printf("-1 -1\n");
        return 0;
    }

    // Проверяем однозначность
    long long first_p = p1_values[0];
    long long first_n = n1_values[0];

    int all_p_same = 1, all_n_same = 1;
    for (int i = 1; i < total; i++) {
        if (p1_values[i] != first_p) all_p_same = 0;
        if (n1_values[i] != first_n) all_n_same = 0;
    }

    long long result_p = all_p_same ? first_p : 0;
    long long result_n = all_n_same ? first_n : 0;

    printf("%lld %lld\n", result_p, result_n);
    return 0;
}