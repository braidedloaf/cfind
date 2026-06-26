#include <stddef.h>
#include <stdio.h>
#include "search.h"
#include <string.h>
#include <ctype.h>

int search_file(const char *path, char *needle, size_t needle_len, const Options *ops) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open file :: %s\n", path);
        return 1;
    }

    char line[4096];
    size_t res_count = 0;

    size_t cur_line = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strlen(line) < needle_len) {
            continue;
        }
        for (size_t i = 0; line[i] != '\0' && i + needle_len < strlen(line); i++) {
            if (ops->ignore_case) {
                strlwr(line);
                strlwr(needle); 
            }
            if (line[i] == needle[0]) {
                if (strncmp(line + i, needle, needle_len) == 0) {
                    print_res(path, line, cur_line, res_count, ops); 
                    
                    res_count++;
                    break;
                }    
            }
        }
        cur_line++;
    }
    
    fclose(file);
    return 0;
}

void print_res(const char *path, char *line, size_t nline, size_t results, const Options *ops) {
    if (ops->no_filename) { //TODO implement
    
    }

    printf("%s:%zu %s", path, nline, line);
}

void strlwr(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}
