#include <stdio.h>
#include <string.h>
#include "search.h"
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    //printf("hello world!\n"); 
    
    if (argc < 3) {
        printf("Usage: %s <search_string> <file1/dir1> [file2/dir2...]\n", argv[0]);
        return 1;
    }
    

    //printf("Calling search with params ::\nSearch_string :: %s\nFilename :: %s\n", argv[1], argv[2]);
    for (int i = 2; i < argc; i++) {
        const char *path = argv[i];
        
        struct stat ist;
        stat(path, &ist);
        
        if (S_ISDIR(ist.st_mode)) {
            //printf("%s is a directory\n", path);
            DIR *dir = opendir(path);
            if (dir == NULL) {
                printf("Failed to open directory :: %s\n", path);
                return 1;
            }
            
            struct dirent *entry;
            struct stat st;
            //printf("not in while loop for %s\n", path);
            while ((entry = readdir(dir)) != NULL) {
                //printf("curentry: %s\n", entry->d_name); 
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                    continue;
                }
                stat(entry->d_name, &st);
                
                //TODO add check for recursive option
                if (S_ISDIR(st.st_mode)) {
                    continue;
                } else {           
                    Result results[100];
                    char fullpath[4096];
                    snprintf(fullpath, sizeof fullpath, "%s/%s", path, entry->d_name);
                    size_t res_cnt = search_file(fullpath, argv[1], strlen(argv[1]), results, 100, NULL);
                    for (size_t j = 0; j < res_cnt; j++) {
                        printf("%s:%zu: %s", results[j].path, results[j].nline, results[j].line);
                    }
                }
            }
            closedir(dir);
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
