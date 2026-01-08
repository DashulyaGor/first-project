#include <stdio.h>
#include <assert.h>

int delim (int a[], int i, int j) {
    int n = 4;
    j = (i + 1) % n;
    int sum = a[i] + a[j];

    int each = sum / 2;
    if (each % 2 == 0) return 1; else return 0;
}


//Тестируем функцию delim
void test_delim () {
    int a[] = {7, 3, 4, 9};
    int rest = 0;
    rest += delim(a, 0, 1);
    assert (a[0] == a[1]);
    assert (a[0] == 5);
    assert (rest == 0);

    rest += delim(a, 2, 3);
    assert (a[2] == a[3]);
    assert (a[2] == 6);
    assert (rest == 1);
}

int main () {
    test_delim();
    return 0;
}