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
    int no_line_numbers;
    int count_only;
    int no_filename;
} Options;


int search_file(const char *filename, char *needle, size_t needle_len, const Options *ops);

int search_dir(const char *path, char *needle, size_t needle_len, const Options *ops);

void print_res(const char *path, char *line, size_t nline, size_t results, const Options *ops);

void strlwr(char *str);

#endif
