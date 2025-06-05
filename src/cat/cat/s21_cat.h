#ifndef S21_CAT
#define S21_CAT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

void print_file(FILE *file, int flags);

#endif