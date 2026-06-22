#include <stdio.h>
#include <string.h>
#include "search.h"

int main(int argc, char **argv) {
    printf("hello world!\n"); 
    
    if (argc < 3) {
        printf("Usage: %s <search_string> <file> [options]\n", argv[0]);
        return 1;
    }
    
    for (int i = 0; i < argc; i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    
   
    FILE *file = fopen(argv[2], "r");

    if (file == NULL) {
        printf("Failed to open file: %s\n", argv[2]);
        return 1;
    }

    printf("Calling search with params ::\nSearch_string :: %s\nFilename :: %s\n", argv[1], argv[2]);

    Result results[100];
    size_t res_cnt = search_file(file, argv[1], strlen(argv[1]), results, 100);
    for (int i = 0; i < res_cnt; i++) {
        printf("%s:%d: %s", argv[2], results[i].nline, results[i].line);
    }
    fclose(file);
    return 0;
}
