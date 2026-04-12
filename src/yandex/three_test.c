#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Структура для хранения кода и номера
typedef struct {
    char code[4];   // 3 цифры + '\0'
    char num[8];    // 7 цифр + '\0'
} Phone;

// Удаляет всё, кроме цифр, и возвращает длину
void extract_digits(const char *input, char *digits) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i])) {
            digits[j++] = input[i];
        }
    }
    digits[j] = '\0';
}

// Парсит номер и заполняет структуру Phone
void parse_phone(const char *s, Phone *p) {
    char digits[12];
    extract_digits(s, digits);
    int len = strlen(digits);

    const char *code_ptr;
    const char *num_ptr;

    if (len == 11) {
        // Формат +7xxx или 8xxx → 11 цифр
        // Код: цифры 1-3 (после 7 или 8)
        if (digits[0] == '8' || (digits[0] == '7')) {
            code_ptr = &digits[1];  // следующие 3 цифры — код
            num_ptr = &digits[4];   // оставшиеся 7 — номер
        } else {
            // На всякий случай: если начинается не с 8/7, но 11 цифр
            code_ptr = &digits[0];
            num_ptr = &digits[3];
        }
    } else if (len == 10) {
        // Формат без 8/+7: код указан явно
        code_ptr = &digits[0];
        num_ptr = &digits[3];
    } else if (len == 7) {
        // Только номер → код = 495
        strcpy(p->code, "495");
        strcpy(p->num, digits);
        return;
    } else {
        // На всякий случай (не должно быть)
        strcpy(p->code, "495");
        strcpy(p->num, "0000000");
        return;
    }

    // Копируем код и номер
    strncpy(p->code, code_ptr, 3);
    p->code[3] = '\0';
    strncpy(p->num, num_ptr, 7);
    p->num[7] = '\0';
}

int main() {
    char target_str[100];
    Phone target, current;

    // Читаем вводимый номер
    fgets(target_str, sizeof(target_str), stdin);
    parse_phone(target_str, &target);

    // Читаем три существующих номера
    for (int i = 0; i < 3; i++) {
        char line[100];
        fgets(line, sizeof(line), stdin);
        parse_phone(line, &current);

        if (strcmp(target.code, current.code) == 0 && strcmp(target.num, current.num) == 0) {
            printf("\nYES\n");
        } else {
            printf("\nNO\n");
        }
    }

    return 0;
}