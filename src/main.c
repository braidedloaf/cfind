#include <stdio.h>
#include <string.h>
#include "search.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    //printf("hello world!\n"); 
    if (argc < 3) {
        printf("Usage: %s [options] <search_string> <file1/dir1> [file2/dir2...]\n", argv[0]);
        return 1;
    }
    Options ops = {0};
    int op;
    while ((op = getopt(argc, argv, "rincf")) != -1) {
        switch(op) {
            case 'r':
                ops.recursive = 1;
                break;

            case 'i':
                ops.ignore_case = 1;
                break;

            case 'n':
                ops.no_line_numbers = 1;
                break;

            case 'c':
                ops.count_only = 1;
                break;

            case 'f':
                ops.no_filename = 1;
                break;

            default:
                printf("default : %c", op);
                return 1;

        }
    }
    for (int i = optind+1; i < argc; i++) {
        const char *path = argv[i];
        struct stat ist;
        stat(path, &ist);
        
        if (S_ISDIR(ist.st_mode)) {
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
                if (S_ISDIR(st.st_mode)) {
                    continue;
                } else {           
                    search_file(fullpath, argv[optind], strlen(argv[optind]), &ops); 
                }
            }
            closedir(dir);
        }
        else {
            search_file(path, argv[optind], strlen(argv[optind]), &ops);
        }
        
    }

    
    return 0;
}
