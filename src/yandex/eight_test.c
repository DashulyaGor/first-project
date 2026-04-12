#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    long long P, V, Q, M;

    // Чтение данных
    scanf("%lld %lld", &P, &V);
    scanf("%lld %lld", &Q, &M);

    // Диапазон Васи: [P - V, P + V]
    long long vasya_left = P - V;
    long long vasya_right = P + V;

    // Диапазон Маши: [Q - M, Q + M]
    long long masha_left = Q - M;
    long long masha_right = Q + M;

    // Общее количество деревьев без учёта пересечения
    long long total = (vasya_right - vasya_left + 1) + (masha_right - masha_left + 1);

    // Пересекаются ли деревья
    long long intersect_left = max(vasya_left, masha_left);
    long long intersect_right = min(vasya_right, masha_right);

    long long intersection = 0;
    if (intersect_left <= intersect_right) {
        intersection = intersect_right - intersect_left + 1;
    }

    // Итоговое количество деревьев
    long long result = total - intersection;

    printf("%lld\n", result);

    return 0;
}