#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<long long> capitals(N);
    for (int i = 0; i < N; ++i) {
        cin >> capitals[i];
    }

    // Кэш: результат для каждого уникального капитала
    map<long long, char> cache;
    vector<char> result(N, '0');

    // Обрабатываем каждое уникальное значение
    set<long long> unique_caps(capitals.begin(), capitals.end());

    for (long long cap : unique_caps) {
        // Собираем всех, кроме одной компании с этим капиталом
        vector<long long> others;
        int count_same = 0;

        for (long long x : capitals) {
            if (x == cap) {
                count_same++;
            } else {
                others.push_back(x);
            }
        }
        // Добавляем остальные из той же группы (их нужно поглотить)
        for (int j = 1; j < count_same; ++j) {
            others.push_back(cap);
        }

        // Сортируем по возрастанию — оптимальный порядок поглощения
        sort(others.begin(), others.end());

        // Симуляция
        long long current = cap;
        bool can_win = true;
        for (long long enemy : others) {
            if (current > enemy) {
                current += enemy;
            } else {
                can_win = false;
                break;
            }
        }

        cache[cap] = can_win ? '1' : '0';
    }

    // Заполняем результат для каждого индекса
    for (int i = 0; i < N; ++i) {
        result[i] = cache[capitals[i]];
    }

    // Вывод
    for (char c : result) {
        cout << c << '\n';
    }

    return 0;
}