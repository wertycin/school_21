#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
void search(int *a, int n);
void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        return 0;
    }
    search(data, n);
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

double mean(int *a, int n) {
    double sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += *p;
    }
    return sum / n;
}

double variance(int *a, int n) {
    double sum_sq = 0;
    for (int *p = a; p - a < n; p++) {
        sum_sq += (*p) * (*p);
    }
    return sum_sq / n - mean(a, n) * mean(a, n);
}

void search(int *a, int n) {
    int candidate = 0;
    double mean_v = mean(a, n);
    double sigma_v = sqrt(variance(a, n));
    for (int *p = a; p - a < n; p++) {
        if (*p % 2 == 0 && *p != 0 && *p >= mean_v && *p <= mean_v + 3 * sigma_v) {
            candidate = *p;
            break;
        }
    }
    printf("%d", candidate);
}
