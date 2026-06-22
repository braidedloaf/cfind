#include <stddef.h>
#include <stdio.h>
#include "search.h"
#include <string.h>

size_t search_file(FILE *file, const char *text, size_t text_len, Result res[], size_t max_res) {
    char line[256];
    size_t res_count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strlen(line) < text_len) {
            continue;
        }
        
        for (int i = 0; line[i] != '\0' && i + text_len < strlen(line); i++) {
            if (line[i] == text[0]) {
                    
            }
        }
    }

    return 0;
}
