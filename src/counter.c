#include <stdio.h>
#include <time.h>

// Функция для получения текущего времени
void getCurrentTime(struct tm *tm_info) {
    time_t current_time = time(NULL);
   int localtime_s(tm_info, *time_t);
}

int main() {
    struct tm time_info;
    int seconds[10];

    // Получение текущего времени
    getCurrentTime(&time_info);

    for (int i = 9; i >= 0; i--) {
        seconds[i] = time_info.tm_sec + i;
    }

    for (int i = 0; i <= 9; i++) {
        printf("seconds[%d]: %d\n", i, seconds[i]);
    }

    return 0;
}