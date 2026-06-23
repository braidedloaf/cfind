#include <stdio.h>
#include <string.h>
#include "search.h"

int main(int argc, char **argv) {
    //printf("hello world!\n"); 
    
    if (argc < 3) {
        printf("Usage: %s <search_string> <file1> [file/dir...]\n", argv[0]);
        return 1;
    }
    

    //printf("Calling search with params ::\nSearch_string :: %s\nFilename :: %s\n", argv[1], argv[2]);
    for (int i = 2; i < argc; i++) {
        const char *path = argv[i];
        if (strchr(path, '.') == NULL) {
            //is a directory
            printf("%s is a directory\n", path);
        }
        else {
            Result results[100];
            size_t res_cnt = search_file(path, argv[1], strlen(argv[1]), results, 100, NULL);
            for (size_t j = 0; j < res_cnt; j++) {
                printf("%s:%zu: %s", results[j].path, results[j].nline, results[j].line);
            }
        }
        
    }

    
    return 0;
}
