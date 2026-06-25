#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stddef.h>

typedef struct {
    size_t nline;
    char line[4096];
    char path[4096];
} Result;

typedef struct {
    int recursive;
    int ignore_case;
    int show_line_numbers;
    int count_only;
    int no_filename;
} Options;


size_t search_file(const char *filename, const char *needle, size_t needle_len, Result res[], size_t max_res, const Options *ops);

#endif
