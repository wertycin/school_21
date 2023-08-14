#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H
#include <stdio.h>
#define SIZE 255

int read_file(FILE *file, char *path);
int write_in_file(FILE *file, char *path);

#endif
