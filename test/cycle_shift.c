#include <stdio.h>
#define NMAX 10
int input(int *a, int *n, int *k);
void output(int *a, int n);
void cycle(int *old, int n, int *new, int k);

int main() {
    int n, old[NMAX];  // Исходный массив
    int k;             // Сдвиг
    int new[NMAX];
    if (input(old, &n, &k)) {
        return 0;
    }
    cycle(old, n, new, k);
    output(new, n);
    return 0;
}

int input(int *a, int *n, int *k) {
    char c;
    if (scanf("%d%c", n, &c) != 2 || c != '\n' || (*n <= 0) || (*n > NMAX)) {
        printf("n/a");
        return 1;
    }
    for (int *p = a; p - a < *n; p++) {
        if ((p - a != *(n)-1 && (scanf("%d%c", p, &c) != 2 || c != ' ')) ||
            (p - a == *(n)-1 && ((scanf("%d%c", p, &c) != 2 || c != '\n')))) {
            printf("n/a");
            return 1;
        }
    }
    if (scanf("%d%c", k, &c) != 2 || (c != '\n' && c != EOF)) {
        printf("n/a");
        return 1;
    }
    return 0;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n - 1; p++) {
        printf("%d ", *p);
    }
    printf("%d", a[n - 1]);
}

void cycle(int *old, int n, int *new, int k) {
    k = k % n;
    if (k < 0) {
        k = n + k;
    }
    for (int i = 0; i < n; i++) {
        if (i >= n - k) {
            new[i] = old[i - (n - k)];
        } else {
            new[i] = old[i + k];
        }
    }
}
