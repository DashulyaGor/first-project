#ifndef S21_CAT
#define S21_CAT
#define CAT_FLAGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>

typedef struct {
    bool number_nonblanck;
    bool show_ends;
    bool number_lines;
    bool squeeze_blanck;
    bool show_tabs;
    bool show_nonprinting;
} Flags;

Flags CatReadFlags(int argc, char *argv[]);
void CatFile(FILE *file, Flags flags, const char *table[static 256]);
void Cat(int argc, char *argv[], Flags flags, const char *table[static 256]);


void CatSetTable(const char *table [static 256]);
void CatSetEnds(const char *table [static 256]);
void CatSetTabs(const char *table [static 256]);
void CatSetNonpriting(const char *table [static 256]);

#endif