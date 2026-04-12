#include <stdio.h>

// Функция округления вверх: ceil(a / b) для положительных a, b
long long ceil_div(long long a, long long b) {
    return (a + b - 1) / b;
}

// Функция вычисления P1 и N1
// Возвращает 1, если успешно, 0 — если ошибка
int compute(long long K, long long M, long long x, long long* p1, long long* n1) {
    if (x <= 0 || M <= 0) return 0;
    long long apartments_per_entrance = M * x;
    if (apartments_per_entrance <= 0) return 0;

    *p1 = (K - 1) / apartments_per_entrance + 1;
    long long pos_in_entrance = (K - 1) % apartments_per_entrance;
    *n1 = pos_in_entrance / x + 1;

    return (*n1 >= 1 && *n1 <= M);
}

int main() {
    long long K1, M, K2, P2, N2;
    int result = scanf("%lld %lld %lld %lld %lld", &K1, &M, &K2, &P2, &N2);
    if (result != 5) {
        printf("-1 -1\n");
        return 0;
    }

    const long long MAX_VAL = 1000000;

    // Проверка диапазона
    if (K1 <= 0 || M <= 0 || K2 <= 0 || P2 <= 0 || N2 <= 0 ||
        K1 > MAX_VAL || M > MAX_VAL || K2 > MAX_VAL || P2 > MAX_VAL || N2 > MAX_VAL) {
        printf("-1 -1\n");
        return 0;
    }
    if (N2 > M) {
        printf("-1 -1\n");
        return 0;
    }

    // L_val * x < K2 <= R_val * x
    long long L_val = (P2 - 1) * M + (N2 - 1);
    long long R_val = (P2 - 1) * M + N2;

    if (R_val <= 0) {
        printf("-1 -1\n");
        return 0;
    }

    // Массивы для хранения возможных (P1, N1)
    long long p1_values[1000], n1_values[1000];
    int total = 0;

    // === Случай 1: L_val == 0 → x >= ceil(K2 / R_val) ===
    if (L_val == 0) {
    long long x_min = ceil_div(K2, R_val);
    
    // Проверим: x_min, x_min+1, x_min+2, x_min*2, MAX_VAL
    long long test_x[] = {x_min, x_min + 1, x_min + 2, x_min * 2, 1000000LL};
    int num_tests = 5;

        for (int i = 0; i < num_tests; i++) {
            long long x = test_x[i];
            if (x < x_min) continue;  // на всякий случай

            long long p1, n1;
            if (compute(K1, M, x, &p1, &n1)) {
                // Проверим, не встречали ли мы уже эту пару
                int found = 0;
                for (int j = 0; j < total; j++) {
                    if (p1_values[j] == p1 && n1_values[j] == n1) {
                        found = 1;
                        break;
                    }
                }
                if (!found && total < 1000) {
                    p1_values[total] = p1;
                    n1_values[total] = n1;
                    total++;
                }
            }

            // Если уже видим неоднозначность — можно раньше выйти
            if (total > 1) {
                long long first_p = p1_values[0];
                long long first_n = n1_values[0];
                int all_p_same = 1, all_n_same = 1;
                for (int j = 1; j < total; j++) {
                    if (p1_values[j] != first_p) all_p_same = 0;
                    if (n1_values[j] != first_n) all_n_same = 0;
                }
                if (!all_p_same && !all_n_same) break;  // уже 0 0
            }
        }
    }

    else {
        long long x_min = ceil_div(K2, R_val);
        long long x_max = (K2 - 1) / L_val;

        if (x_min > x_max || x_min <= 0) {
            printf("-1 -1\n");
            return 0;
        }

        // Если диапазон слишком большой — проверим начало и конец
        const long long MAX_RANGE = 100000;
        if (x_max - x_min + 1 > MAX_RANGE) {
            long long x_tests[] = {x_min, x_max};
            for (int i = 0; i < 2; i++) {
                long long x = x_tests[i];
                long long base = (P2 - 1) * M * x;
                long long start_floor = base + (N2 - 1) * x + 1;
                long long end_floor = base + N2 * x;

                if (K2 >= start_floor && K2 <= end_floor) {
                    long long p1, n1;
                    if (compute(K1, M, x, &p1, &n1)) {
                        p1_values[total] = p1;
                        n1_values[total] = n1;
                        total++;
                    }
                }
            }
        } else {
            // Перебираем все x
            for (long long x = x_min; x <= x_max; x++) {
                long long base = (P2 - 1) * M * x;
                long long start_floor = base + (N2 - 1) * x + 1;
                long long end_floor = base + N2 * x;

                if (K2 < start_floor || K2 > end_floor) continue;

                long long p1, n1;
                if (compute(K1, M, x, &p1, &n1)) {
                    p1_values[total] = p1;
                    n1_values[total] = n1;
                    total++;
                }
            }
        }
    }

    // Если нет ни одного подходящего x
    if (total == 0) {
        printf("-1 -1\n");
        return 0;
    }

    // === Проверяем однозначность P1 и N1 НЕЗАВИСИМО ===
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