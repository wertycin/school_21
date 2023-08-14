CC = gcc -Wall -Werror -Wextra
build = ../build/
all: cipher

cipher: file_processing.o cipher.o
	$(CC) file_processing.o cipher.o -o $(build)cipher

file_processing.o: file_processing.c
	$(CC) file_processing.c -c

cipher.o: cipher.c
	$(CC) cipher.c -c

clean:
	rm *.o ../build/*

rebuild: clean all
