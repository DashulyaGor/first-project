#include <stdio.h>
#include <stdbool.h>

int min_knights(int n, int* answers) {
    int knight1 = 0, valid1 = 1;
    int knight2 = 0, valid2 = 1;

    int real_roles[n];

    // Сценарий 1: первый человек — рыцарь
    real_roles[0] = 1;
    for (int i = 1; i < n; ++i) {
        int left_neighbor = (i - 1 + n) % n;
        int real_left_status = real_roles[left_neighbor];
        int expected_answer = real_roles[i] ? real_left_status : !real_left_status;

        if (expected_answer != answers[i]) {
            valid1 = 0;
            break;
        }

        // Определяем реальный статус текущего человека
        real_roles[i] = answers[i]; // Рыцарь говорит правду → статус соседа = ответ
    }

    // Проверка цикличности для первого сценария
    int last_index = n - 1;
    int real_left_status_last = real_roles[(last_index - 1 + n) % n];
    int expected_answer_last = real_roles[last_index] ? real_left_status_last : !real_left_status_last;
    if (expected_answer_last != answers[last_index]) {
        valid1 = 0;
    }

    // Подсчёт рыцарей в первом сценарии
    if (valid1) {
        for (int i = 0; i < n; ++i) {
            knight1 += real_roles[i];
        }
    }

    // Сценарий 2: первый человек — лжец

    real_roles[0] = 0;
    for (int i = 1; i < n; ++i) {
        int left_neighbor = (i - 1 + n) % n;
        int real_left_status = real_roles[left_neighbor];
        int expected_answer = real_roles[i] ? real_left_status : !real_left_status;

        if (expected_answer != answers[i]) {
            valid2 = 0;
            break;
        }

        // Лжец лжёт → статус соседа = !ответ
        real_roles[i] = !answers[i];
    }

    // Проверка цикличности для второго сценария
    real_left_status_last = real_roles[(last_index - 1 + n) % n];
    expected_answer_last = real_roles[last_index] ? real_left_status_last : !real_left_status_last;
    if (expected_answer_last != answers[last_index]) {
        valid2 = 0;
    }

    // Подсчёт рыцарей во втором сценарии
    if (valid2) {
        for (int i = 0; i < n; ++i) {
            knight2 += real_roles[i];
        }
    }

    if (valid1 && valid2)
        return knight1 <= knight2 ? knight1 : knight2;
    else if (valid1)
        return knight1;
    else if (valid2)
        return knight2;
    else {
        bool all_same_answers = true;
            for (int i = 1; i < n; ++i) {
                if (answers[i] != answers[0]) {
                all_same_answers = false;
                break;
            }
        }
        if (all_same_answers && answers[0] == 1) {
            return 0; // Все жители говорят одинаково и утверждают одно и то же (это возможно, если все лжецы)
        } else {
            return 1; // Если нет единогласия, минимальный результат — 1 рыцарь
        }
    }
}

int main() {
    int n;

    scanf("%d", &n);

    int answers[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &answers[i]);
    }

    // Вычисляем минимальное количество рыцарей
    int result = min_knights(n, answers);
    printf("%d\n", result);

    return 0;
}