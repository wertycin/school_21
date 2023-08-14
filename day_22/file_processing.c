#include "file_processing.h"

#include <string.h>

int read_file(FILE *file, char *path) {
    int rtn = 1;
    scanf("%255s", path);
    file = fopen(path, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long pos = ftell(file);
        if (pos > 0) {
            char string[SIZE];
            rewind(file);
            while (fgets(string, sizeof(string), file)) {
                printf("%s", string);
            }
        } else {
            rtn = 0;
        }
        fclose(file);
    } else {
        rtn = 0;
    }
    if (rtn) {
        printf("\n");
    }
    return rtn;
}

int write_in_file(FILE *file, char *path) {
    int rtn = 1;
    char string[SIZE];
    getchar();
    fgets(string, SIZE, stdin);
    if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = '\0';
    file = fopen(path, "r+");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long pos = ftell(file);
        if (pos != 0) fprintf(file, "%c", '\n');
        fprintf(file, "%s", string);
        rewind(file);
        while (fgets(string, sizeof(string), file)) {
            printf("%s", string);
        }
        fclose(file);
    } else {
        rtn = 0;
    }
    if (rtn) {
        printf("\n");
    }
    return rtn;
}
