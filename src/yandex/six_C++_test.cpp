#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;

    string result = "";

    // Обходим строку с конца
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == '#') {
            // Берём два символа перед '#'
            int num = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            result += 'a' + num - 1;  // 'j' = 'a' + 9, но num=10 → 'a'+10-1 = 'j'
            i -= 2;  // пропускаем две цифры
        } else {
            // Одна цифра: от 1 до 9
            int num = s[i] - '0';
            result += 'a' + num - 1;  // 'a'=1 → 'a'+1-1='a'
        }
    }

    // Так как мы шли с конца, переворачиваем результат
    reverse(result.begin(), result.end());

    cout << result << endl;

    return 0;
}