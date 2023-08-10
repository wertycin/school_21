CC = gcc -Wall -Werror -Wextra
build = ../build/
all: door_struct list_test stack_test

door_struct: dmanager_module.o
	$(CC) dmanager_module.o -o $(build)Quest_1

dmanager_module.o: dmanager_module.c
	$(CC) dmanager_module.c -c

list_test: list.o list_test.o
	$(CC) list.o list_test.o -o $(build)Quest_2

list.o: list.c
	$(CC) list.c -c

list_test.o: list_test.c
	$(CC) list_test.c -c

stack_test: stack.o stack_test.o
	$(CC) stack.o stack_test.o -o $(build)Quest_3

stack.o: stack.c
	$(CC) stack.c -c

stack_test.o: stack_test.c
	$(CC) stack_test.c -c

clean:
	rm *.o ../build/*

rebuild: clean all
