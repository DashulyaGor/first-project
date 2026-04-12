#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solve(int n, vector<long long>& comp) {
    if (n == 1) {
        return {1};
    }

    long long now_sum = comp[0];         // сумма от начала до текущей компании
    int first_winner = n;                // первая компания, проходящая условия
    int last_loser = 0;                  // последняя "слабая" позиция

    // Проходим от i=1 до n-2 (включительно)
    for (int i = 1; i < n - 1; ++i) {
        now_sum += comp[i];

        // Условие: рост + сумма > следующий
        if (comp[i] > comp[i - 1] && now_sum > comp[i + 1]) {
            if (first_winner == n) {
                first_winner = i;
            }
        }

        // Если сумма не перешагнула следующего — это проигрыш
        if (now_sum <= comp[i + 1]) {
            last_loser = i;
        }
    }

    // Позиция, с которой начинаются победители
    int winner_pos = max(first_winner, last_loser + 1);

    // Формируем ответ: [0, ..., 0, 1, ..., 1]
    vector<int> ans(n, 0);
    for (int i = winner_pos; i < n; ++i) {
        ans[i] = 1;
    }

    // Особое условие для последнего элемента
    if (comp[n - 1] > comp[n - 2]) {
        ans[n - 1] = 1;
    }

    return ans;
}

int main() {
    int n;
    cin >> n;

    vector<long long> comp(n);
    for (int i = 0; i < n; ++i) {
        cin >> comp[i];
    }

    vector<int> result = solve(n, comp);

    // Выводим результат через пробел
    for (int i = 0; i < n; ++i) {
        cout << result[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;

    return 0;
}