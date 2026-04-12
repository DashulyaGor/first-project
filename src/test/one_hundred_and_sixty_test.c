#include <stdio.h>
#include <string.h>

// Фиксированные значения баз
const unsigned long long bases[] = {1, 20, 360, 7200, 129600};

unsigned long long calculate(const char *line) {
    int stars = 0, dashes = 0;
    
    // Проверка специальной строки '@'
    if (strcmp(line, "@") == 0) {
        return 0; // Если это спецсимвол, возвращаем ноль
    }
    
    // Подсчет звёзд и дефисов
    for (size_t i = 0; line[i]; ++i) {
        if (line[i] == '*') stars++;
        if (line[i] == '-') dashes++;
    }

    // Сумма звезд и дефисов
    return stars + dashes * 5;

}

int main() {
    unsigned long long result = 0;
    int rank = 1;
    
    // Цикл по строкам
    char line[100];
    while (fgets(line, sizeof(line), stdin)) {
        size_t len = strlen(line);
        if (line[len - 1] == '\n') line[--len] = '\0'; // Удаляем перенос строки

        if (len == 0) break;
    
        // Обрабатываем текущую строку
        unsigned long long value = calculate(line);
    
        // Суммируем результат с учётом ранга
        result += value * bases[rank - 1];
    
        rank++; // Увеличиваем ранг
    }

    printf("%llu\n", result);
    return 0;
}