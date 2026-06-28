#include <stddef.h>
#include <stdio.h>
#include "search.h"
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

int search_file(const char *path, const char *oneedle, size_t needle_len, const Options *ops) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open file :: %s\n", path);
        return 1;
    }

    char line[4096];
    size_t res_count = 0;
    size_t not_count = 0;
    
    size_t cur_line = 1;
    //TODO make its own lwr needle change header to const char 
    char needle[needle_len+1];
    memcpy(needle, oneedle, needle_len);
    needle[needle_len] = '\0';
    if (ops->ignore_case) {
        strlwr(needle);
    }
    

    while (fgets(line, sizeof(line), file) != NULL) {
        size_t line_len = strlen(line);
        if (line_len < needle_len) {
            cur_line++;
            continue;
        }
        if (ops->ignore_case) {
            strlwr(line);
        }
        int found = 0;
        for (size_t i = 0; line[i] != '\0' && i + needle_len < line_len; i++) {
            if (line[i] == needle[0]) {
                if (strncmp(line + i, needle, needle_len) == 0) {
                    if (!(ops->count_only) && !(ops->invert_match)) {
                        print_res(path, line, cur_line, res_count, ops); 
                    }
                    found = 1;
                    res_count++;
                    break;
                }
            }
        }
        if (found == 0 && ops->invert_match) {
            if (!(ops->count_only)) {
                print_res(path, line, cur_line, not_count, ops);
            }
            not_count++;
        }
        cur_line++;
    }
    if (ops->count_only) {
        if (ops->invert_match) {
            print_res(path, line, cur_line, not_count, ops);
        } else {
            print_res(path, line, cur_line, res_count, ops);
        }
    }
    
    fclose(file);
    return 0;
}

int search_dir(const char *path, const char *needle, size_t needle_len, const Options *ops) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Failed to open directory :: %s\n", path);
        return 1;
    }

    struct dirent *entry;
    struct stat st;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char fullpath[4096];
        snprintf(fullpath, sizeof fullpath, "%s/%s", path, entry->d_name);
        stat(fullpath, &st);
        if (S_ISDIR(st.st_mode) && ops->recursive) {
            search_dir(fullpath, needle, needle_len, ops);
        } else {           
            search_file(fullpath, needle, needle_len, ops); 
        }
    }
    closedir(dir);

    return 0;
}


void print_res(const char *path, char *line, size_t nline, size_t results, const Options *ops) {  
    printf("%s:", path);
    if (ops->count_only) {
        printf("%zu", results);
        printf("\n");
    } else {
        if (ops->line_numbers) {
            printf("%zu:", nline);
        }
        printf("%s", line);
    }
}

void strlwr(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

