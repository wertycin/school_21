#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("n/a");
        exit(0);
    }
    int a[n][n];
    int sloy = 0;
    int k = 1;
    while (k < n * n - 2) {
        for (int i = sloy; i < n - 1 - sloy; i++) {
            a[sloy][i] = k++;
        }
        for (int i = sloy; i < n - 1 - sloy; i++) {
            a[i][n - 1 - sloy] = k++;
        }
        for (int i = n - 1 - sloy; i > sloy; i--) {
            a[n - 1 - sloy][i] = k++;
        }
        for (int i = n - 1 - sloy; i > sloy; i--) {
            a[i][sloy] = k++;
        }
        sloy++;
    }
    if (n % 2) a[n / 2][n / 2] = k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf("%d ", a[i][j]);
        }
        if (i < n - 1) printf("%d\n", a[i][n - 1]);
    }
    printf("%d", a[n - 1][n - 1]);
}