#!/bin/bash

# Утилита, которую вы тестируете
S21_CAT="./s21_cat"

# Путь к оригинальной утилите cat
ORIGINAL_CAT="/usr/bin/cat"

# Временные файлы для сравнения
OUTPUT_S21_CAT="output_s21_cat.txt"
OUTPUT_ORIGINAL_CAT="output_original_cat.txt"

# Тестовые файлы
TEST_FILE1="1.txt"

# Функция для выполнения теста
run_test() {
    local flags="$1"
    shift
    local files="$@"

    # Запуск вашей утилиты
    $S21_CAT $flags $files > $OUTPUT_S21_CAT

    # Запуск оригинальной утилиты
    $ORIGINAL_CAT $flags $files > $OUTPUT_ORIGINAL_CAT

    # Сравнение результатов
    if diff $OUTPUT_S21_CAT $OUTPUT_ORIGINAL_CAT > /dev/null ; then
        echo "Test with flags '$flags' and files '$files': PASS"
    else
        echo "Test with flags '$flags' and files '$files': FAIL"
        diff $OUTPUT_S21_CAT $OUTPUT_ORIGINAL_CAT
    fi
}

# Тесты для разных комбинаций флагов и файлов
run_test "" "$TEST_FILE1"
run_test "-s" "$TEST_FILE1"
run_test "-n" "$TEST_FILE1"
run_test "-b" "$TEST_FILE1"
run_test "-e" "$TEST_FILE1"
run_test "-E" "$TEST_FILE1"
run_test "-t" "$TEST_FILE1"
run_test "-T" "$TEST_FILE1"

# Удаление временных файлов после тестов
rm $output_S21_CAT $OUTPUT_ORIGINAL_CAT