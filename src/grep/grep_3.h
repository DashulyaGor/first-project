#ifndef GREP_3
#define GREP_3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <unistd.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>


#define pcre2_compile PCRE2_SUFFIX(pcre2_compile_)
#define pcre2_code PCRE2_SUFFIX(pcre2_code_)
#define pcre2_get_ovector_pointer PCRE2_SUFFIX(pcre2_get_ovector_pointer_)

#endif