#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stddef.h>

typedef struct {
    int recursive;
    int ignore_case;
    int line_numbers;
    int count_only;
    int invert_match;
} Options;


int search_file(const char *filename, char *needle, size_t needle_len, const Options *ops);

int search_dir(const char *path, char *needle, size_t needle_len, const Options *ops);

void print_res(const char *path, char *line, size_t nline, size_t results, const Options *ops);

void strlwr(char *str);

#endif
