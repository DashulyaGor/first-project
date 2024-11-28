#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct cat {
  int b;
  int e;
  int s;
  int t;
  int n;
  int v;
  int sumStr;
  FILE *file;
} p;

void init();
void options(char arg);
int process_file(char *argv[], size_t count);

#endif  // SRC_CAT_S21_CsAT_H_