#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stddef.h>

typedef struct {
    size_t nline;
    char line[256];
} Result;

size_t search_file(FILE *file, const char *text, size_t text_len, Result res[], size_t max_res);

#endif
