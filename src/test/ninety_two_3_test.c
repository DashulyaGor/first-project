#include <stdio.h>

#define BUS_A 360
#define BUS_B 345

typedef struct {
    int h;
    int m;
} Time;

int time2min(Time t) {
    if (t.h >= 0 && t.h < 24 && t.m >= 0 && t.m < 60) {
        return t.h * 60 + t.m;
    } else {
        return -1;
    }
}

int wait_bus(Time clock, int first_departure, int interval) {
    int current = time2min(clock);

    if(current <= first_departure) {
        return first_departure - current;
    } else {
        int diff = current - first_departure;
        if(diff % interval == 0) {
            return 0;
        } else {
            return interval - (diff % interval);
        }
    }
}

int main() {
    int h, m, t1, t2;
    char choice;

    scanf("%d %d %d %d", &h, &m, &t1, &t2);

    Time arrival = {h, m};

    if (time2min(arrival) < 330) {
        return 0;
    }

    int wait_a = wait_bus(arrival, BUS_A, t1);
    int wait_b = wait_bus(arrival, BUS_B, t2);

    if (wait_a < wait_b) {
        choice = 'A';
    } else {
        choice = 'B';
    }

    printf("%d\n%d\n%c\n", wait_a, wait_b, choice);
    return 0;
}