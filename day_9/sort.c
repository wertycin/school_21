#include <stdio.h>
#define LENGTH 10

int input(int *a);
void sort(int *a);
void output(int *a);

int main() {
    int data[LENGTH];
    if (input(data)) {
        return 0;
    }
    sort(data);
    output(data);
    return 0;
}

int input(int *a) {
    char c;
    for (int *p = a; p - a < LENGTH; p++) {
        if ((p - a != LENGTH - 1 && (scanf("%d%c", p, &c) != 2 || c != ' ')) ||
            (p - a == LENGTH - 1 && ((scanf("%d%c", p, &c) != 2 || (c != '\n' && c != EOF))))) {
            printf("n/a");
            return 1;
        }
    }
    return 0;
}

void sort(int *a) {
    for (int i = 1; i < LENGTH; i++) {
        for (int j = i; j > 0 && a[j - 1] > a[j]; j--) {
            int buf;
            buf = a[j];
            a[j] = a[j - 1];
            a[j - 1] = buf;
        }
    }
}

void output(int *a) {
    for (int *p = a; p - a < LENGTH - 1; p++) {
        printf("%d ", *p);
    }
    printf("%d", a[LENGTH - 1]);
}
