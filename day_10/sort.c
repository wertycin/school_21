#include <stdio.h>
#include <stdlib.h>

int input(int *a, int n);
void sort(int *a, int n);
void output(int *a, int n);

int main() {
    int n;
    char c;
    if (scanf("%d%c", &n, &c) != 2 || c != '\n' || n < 1) {
        printf("n/a");
        return 0;
    }
    int *data = malloc(sizeof(int) * n);
    if (data == NULL) {
        printf("n/a");
    }
    if (input(data, n)) {
        return 0;
    }
    sort(data, n);
    output(data, n);
    free(data);
    return 0;
}

int input(int *a, int n) {
    char c;
    for (int *p = a; p - a < n; p++) {
        if ((p - a != n - 1 && (scanf("%d%c", p, &c) != 2 || c != ' ')) ||
            (p - a == n - 1 && ((scanf("%d%c", p, &c) != 2 || (c != '\n' && c != EOF))))) {
            printf("n/a");
            return 1;
        }
    }
    return 0;
}

void sort(int *a, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && a[j - 1] > a[j]; j--) {
            int buf;
            buf = a[j];
            a[j] = a[j - 1];
            a[j - 1] = buf;
        }
    }
}

void output(int *a, int n) {
    for (int *p = a; p - a < n - 1; p++) {
        printf("%d ", *p);
    }
    printf("%d", a[n - 1]);
}
