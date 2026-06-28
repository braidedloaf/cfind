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
            search_dir(path, argv[optind], strlen(argv[optind]), &ops);
        }
        else {
            search_file(path, argv[optind], strlen(argv[optind]), &ops);
        }
        
    }

    
    return 0;
}
