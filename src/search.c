#include <stddef.h>
#include <stdio.h>
#include "search.h"
#include <string.h>

size_t search_file(const char *path, const char *needle, size_t needle_len, Result res[], size_t max_res, const Options *ops) {
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
            if (res_count < max_res) {
                if (line[i] == needle[0]) {
                    if (strncmp(line + i, needle, needle_len) == 0) {
                        res[res_count] = (Result) {.nline = cur_line };
                        snprintf(res[res_count].line, sizeof res[res_count].line, "%s", line); 
                        snprintf(res[res_count].path, sizeof res[res_count].path, "%s", path); 
                        
                        res_count++;
                        break;
                    }
                }    
            }
        }
        cur_line++;
    }
    
    fclose(file);
    return res_count;
}
