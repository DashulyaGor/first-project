#include <stdio.h>

#define MAX_ID 1001

int main() {
    int n;
    scanf("%d", &n);

    int seen[MAX_ID] = {0};  // seen[id] = 1, если клиент с таким id уже встречался
    int count = 0;

    for (int i = 0; i < n; i++) {
        int timestamp, id, recept_id;
        scanf("%d %d %d", &timestamp, &id, &recept_id);

        if (id < 1 || id >= MAX_ID) continue;  // Защита от некорректных id, хотя по условию 0 < id <= 1000

        if (!seen[id]) {
            seen[id] = 1;
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
