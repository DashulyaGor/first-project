#include <stdio.h>

typedef struct {
    int h;
    int min;
} TicTac;

TicTac after(TicTac a, int min);
void forward(TicTac *me, TicTac a);
void backward(TicTac *me, TicTac a);
int isEqualTime(TicTac a, TicTac b);
void printTic(TicTac a);

int main() {
    TicTac a, b, c;
    int mk;

    scanf("%02d:%02d", &(a.h), &(a.min));
    scanf("%d", &mk);
    scanf("%02d:%02d", &(b.h), &(b.min));

    printf("equal: %d\n", isEqualTime(a, b));
    c = after(a, mk);
    printf("after: ");
    printTic(c);

    c = a;
    printf("forward: ");
    forward(&a, b);
    printTic(a);

    printf("backward: ");
    backward(&c, b);
    printTic(c);

    return 0;
}

int time2min(TicTac t) {
    return t.h * 60 + t.min;
}

TicTac min2time(int mm) {
    return (TicTac){(mm / 60) % 12, mm % 60};
}

TicTac after(TicTac a, int min) {
    TicTac res = a;
    int t = time2min(res);
    t += min;
    res = min2time(t);
    if (res.h == 12) {
        res.h = 00;
    } else if (res.h > 12) {
        res.h++;
    } else if (res.min == 60) {
        res.min = 00;
    } else if (res.min > 60) {
        res.h++;
    }
    return res;
}

void forward(TicTac *me, TicTac a) {
    me->h += a.h;
    me->min += a.min;
    TicTac res = *me;
    int t = time2min(res);
    res = min2time(t);
    if (res.h == 12) {
        res.h = 00;
    } else if (res.h > 12) {
        res.h++;
    } else if (res.min == 60) {
        res.min = 00;
    } else if (res.min > 60) {
        res.h++;
    }
    *me = res;
}

void backward(TicTac *me, TicTac a) {
    me->h -= a.h;
    me->min -= a.min;
    TicTac res = *me;

    if (res.h == 12) {
        res.h = 00;
    } else if (res.min == 60) {
        res.min = 00;
    } else if (res.min < 00) {
        res.h = 12 - 1;
        res.min = 60 - a.min;
    }

    *me = res;
}

int isEqual(TicTac a, TicTac b) {
    return a.h == b.h && a.min == b.min;
}

int isEqualTime(TicTac a, TicTac b) {
    int res;
    res = isEqual(a, b);
    return res ? 1 : 0;
}

void printTic(TicTac a) {
    printf("%02d:%02d\n", a.h, a.min);
}