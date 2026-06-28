#include <stddef.h>
#include <stdio.h>
#include "search.h"
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

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

int search_dir(const char *path, char *needle, size_t needle_len, const Options *ops) {
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
        //TODO add check for recursive option
        if (S_ISDIR(st.st_mode) && ops->recursive) {
            printf("is recuring with -r over %s\n", fullpath);
            search_dir(fullpath, needle, needle_len, ops);
        } else {           
            search_file(fullpath, needle, needle_len, ops); 
        }
    }
    closedir(dir);

    
    return 0;
}


void print_res(const char *path, char *line, size_t nline, size_t results, const Options *ops) {
    if (ops->no_filename) { //TODO implement
         
    }
    
    
    printf(strchr(line, '\n') != NULL ? "%s:%zu %s" : "%s:%zu %s\n", path, nline, line);
}

void strlwr(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}
