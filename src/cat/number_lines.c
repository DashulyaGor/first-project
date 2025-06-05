#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для подсчета количества строк в файле
int number_lines(const char* filename) {
    int number_lines = 0;
    
    // Открытие файла для чтения
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return -1;
    }

    // Динамически выделяем память под строку
    size_t line_size = 1024;
    char* line = malloc(line_size);
    if (!line) {
        fprintf(stderr, "Не удалось выделить память.\n");
        fclose(file);
        return -1;
    }

    // Считываем файл построчно и увеличиваем счётчик
    while (fgets(line, line_size, file)) {
        number_lines++;
    }

    free(line);   // Освобождаем выделенную память
    fclose(file); // Закрываем файл

    printf("Количество строк в файле: %d\n", number_lines);
    return number_lines;
}

int main() {
    const char* filename = "1.txt";
    int result = number_lines(filename);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}