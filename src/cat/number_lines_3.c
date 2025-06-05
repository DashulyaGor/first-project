#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file_and_count_lines(const char* filename) {
    int line_number = 1;  // Начальный номер строки
    // int line_count = 0;

    // Открытие файла для чтения
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Something went wrong!");
        exit(EXIT_FAILURE);
    }

    // Динамически выделяем память под строку
    size_t line_size = 1024;
    char* line = malloc(line_size);
    if (!line) {
        fprintf(stderr, "Memory could not be allocated.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Считываем файл построчно и увеличиваем счётчики
    while (fgets(line, line_size, file)) {
        printf("%d %s", line_number++, line);  // Вывод номера строки и самой строки
    }

    free(line);   // Освобождаем выделенную память
    fclose(file); // Закрываем файл

   
    printf("\n");


    // printf("\nКоличество строк в файле: %d\n", line_count);
}

int main() {
    const char* filename = "1.txt";
    print_file_and_count_lines(filename);
    return EXIT_SUCCESS;
}