#include <stdio.h>
#include <assert.h>

#define DESKSIZE 52

struct Card {
    char rank;
    char suit;
};

int check(struct Card * hand);

int main() {
    struct Card hand1 [] = {{'Q', 's'}, {'A','h'}, {'9', 'd'}, {0, 0}};
    struct Card hand2 [] = {{'2', 's'}, {'A','h'}, {0, 0}};
    assert(1 == check(hand1));
    assert(0 == check(hand2));

    return 0;
}

int check(struct Card * hand) {
    struct Card * p;
    for(p = hand; p->rank != 0; p++) {
        if (p->rank == 'Q' && p->suit == 's') {
            return 1;
        }
    }
    return 0;
}
