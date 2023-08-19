#include <stdio.h>

struct Human {
 //   char name[10];
    int height;
    int weight;
    struct Human* ptr;
    struct dog* dog;
};

struct dog
{
    char name[10];
};


int main() {
    struct Human Nayana;
    struct Human Ivan;
    Nayana.ptr = &Ivan;
    struct dog dog = {"Bob"};
    Ivan.dog = &dog;  
    struct Human Katuha;
    Ivan.ptr = &Katuha;
    printf("%s", (*Ivan.dog).name);
    return 0;
}