#include <stdio.h>

struct Time {
    int h;
    int m;
};

void printTime(struct Time t) {
    printf("%02d:%02d\n", t.h, t.m);
}

struct Time read_Time() {
    struct Time res;
    scanf("%d:%d", &res.h, &res.m);
    return res;
}

void scan_Time(struct Time *p) {
    scanf("%d:%d", &p->h, &p->m);
}

int main() {
    struct Time t1, t2;
    t1 = read_Time();
    scan_Time(&t2);

    printTime(t1);
    printTime(t2);

    return 0;
}