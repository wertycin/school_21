#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        return 0;
    };
    squaring(data, n);
    output(data, n);

    return 0;
}

int input(int *a, int *n) {
    char c;
    if (scanf("%d%c", n, &c) != 2 || c != '\n' || (*n <= 0) || (*n > NMAX)) {
        printf("n/a");
        return 1;
    }
    for (int *p = a; p - a < *n; p++) {
        if ((p - a != *(n)-1 && (scanf("%d%c", p, &c) != 2 || c != ' ')) ||
            (p - a == *(n)-1 && ((scanf("%d%c", p, &c) != 2 || (c != '\n' && c != EOF))))) {
            printf("n/a");
            return 1;
        }
    }
    return 0;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n - 1; p++) {
        printf("%d ", *p);
    }
    printf("%d", a[n - 1]);
}

void squaring(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        *p = (*p) * (*p);
    }
}
