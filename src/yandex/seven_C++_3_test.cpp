#include <iostream>
#include <vector>
using namespace std;

vector<int> solve(int n, vector<long long>& comp) {
    if (n == 1) return {1};

    vector<int> ans(n, 0);
    long long prefix_sum = comp[0];
    int first_valid = n;
    int last_insufficient = 0;

    for (int i = 1; i < n - 1; ++i) {
        prefix_sum += comp[i];
        if (comp[i] > comp[i-1] && prefix_sum > comp[i+1]) {
            if (first_valid == n) first_valid = i;
        }
        if (prefix_sum <= comp[i+1]) {
            last_insufficient = i;
        }
    }

    int min_index = max(first_valid, last_insufficient + 1);
    for (int i = min_index; i < n; ++i) ans[i] = 1;
    if (n >= 2 && comp[n-1] > comp[n-2]) ans[n-1] = 1;

    return ans;
}

int main() {
    int n; cin >> n;
    vector<long long> comp(n);
    for (int i = 0; i < n; ++i) cin >> comp[i];
    auto res = solve(n, comp);
    for (int i = 0; i < n; ++i) {
        cout << res[i];
        if (i < n-1) cout << " ";
    }
    cout << endl;
    return 0;
}