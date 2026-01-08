#include <stdio.h>
#include <assert.h>


int all_equal(int a[], int n) {
    n = 4;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[0]) {
            return 0;
        }
    }
    return 1;
}

void test_all_equal()
{
    int a[] = {2, 2, 2, 3};
    int b[] = {-1, -3, -3};


    assert(all_equal(a, 3));
    assert(!all_equal(a, 4));
    assert(all_equal(b, 1));
    assert(!all_equal(b, 3));
}


int main()
{
    test_all_equal();
    return 0;
}