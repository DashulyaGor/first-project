#include <stdio.h>

int main() {
    unsigned k, p1, p2, p3;
    
    scanf("%u%u%u%u", &k, &p1, &p2, &p3);

    if (p1 + p2 + p3 <= k) {
        printf("YES\n");
    } else if ((p1 + p2 <= k && p3 <= k) || (p1 + p3 <= k && p2 <= k) || (p2 + p3 <= k && p1 <= k)) {
        printf("YES\n");
    //} else if (p1 <= k && p2 <= k && p3 <= k) {
        //printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}