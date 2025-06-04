#include <stdio.h>
#include <assert.h>

struct Time {
    int h;
    int m;
};

void print_time(struct Time t);
int time2min(struct Time t);
struct Time min2time(int mm);
int is_equal(struct Time t1, struct Time t2);
struct Time add(struct Time t1, struct Time t2);



int main() {
    struct Time t1 = {22, 55};
    struct Time dt = {2, 7};
    struct Time t2, expected_res = {1, 2};
    print_time(t1);
    print_time(dt);
    int mm = time2min(dt);  // 2:07
    assert(mm == 127);
    printf("%d\n", mm);
    struct Time t = min2time(127);
    print_time(t);
    assert(1 == is_equal(min2time(127), dt));
    //assert(is_equal(min2time(127), dt));
    t2 = add(t1, dt);
    print_time(t2);
    assert(1 == is_equal(t2, expected_res));
    return 0;
}

void print_time(struct Time t) {
    printf("%02d:%02d\n", t.h, t.m);
}

int time2min(struct Time t)
{
    int res;
    res = t.h * 60 + t.m;
    return res;
}

struct Time min2time(int mm) {
    struct Time res;
    res.m = mm % 60;
    res.h = mm / 60 % 24;
    return res;
    //return (struct Time){mm / 60 % 24, mm % 60};
}

/*
struct Time min2time(int mm) {
    struct Time res = {
        .m = mm % 60,
        .h = mm / 60 % 24
        };
    return res;
}*/

int is_equal(struct Time t1, struct Time t2) {
    if (t1.h != t2.h)
        return 0;
    if (t1.m != t2.m)
        return 0;
    return 1;
    //return t1.h == t2.h && t1.m == t2.m;
}

struct Time add(struct Time t1, struct Time t2) {
    int mmres = time2min(t1) + time2min(t2);
    struct Time res = min2time(mmres);
    return res;
}