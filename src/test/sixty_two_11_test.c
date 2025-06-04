#include <stdio.h>

struct Vector {
    float x;
    float y;
};

int main() {
    struct Vector vec;
    int x = 2, y = 3;

    vec.x = y;
    vec.y = y;
    
    return 0;
}