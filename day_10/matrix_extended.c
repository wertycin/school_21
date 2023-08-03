#include <stdio.h>
#include <stdlib.h>

int input(int **a, int n, int m);
void output(int **a, int n, int m);
void simplest(int n, int m);
void medium(int M, int N);
void hardest(int M, int N);
void statik(int M, int N);
void str_max(int **a, int n, int m);
void colomn_min(int **, int, int);

int main() {
    int n, m, choose;
    if (scanf("%d", &choose) != 1 || choose < 1 || choose > 4) {
        printf("n/a");
        return 0;
    }
    if (scanf("%d %d", &n, &m) != 2 || n < 1 || m < 1) {
        printf("n/a");
        return 0;
    }
    switch (choose) {
        case 1:
            statik(n, m);
            break;
        case 2:
            simplest(n, m);
            break;
        case 3:
            medium(n, m);
            break;
        case 4:
            hardest(n, m);
        default:
            break;
    }
    return 0;
}

void simplest(int M, int N) {
    int **pointer_array = malloc(M * sizeof(int *));

    for (int i = 0; i < M; i++) pointer_array[i] = malloc(N * sizeof(int *));
    if (input(pointer_array, M, N)) {
        exit(0);
    }
    output(pointer_array, M, N);
    str_max(pointer_array, M, N);
    colomn_min(pointer_array, M, N);

    for (int i = 0; i < M; i++) free(pointer_array[i]);

    free(pointer_array);
}

void medium(int M, int N) {
    int **pointer_array = malloc(M * sizeof(int *));
    int *values_array = malloc(M * N * sizeof(int));
    for (int i = 0; i < M; i++) pointer_array[i] = values_array + N * i;
    if (input(pointer_array, M, N)) {
        exit(0);
    }
    output(pointer_array, M, N);
    str_max(pointer_array, M, N);
    colomn_min(pointer_array, M, N);
    free(values_array);
    free(pointer_array);
}

void hardest(int M, int N) {
    int **single_arr = malloc(M * N * sizeof(int) + M * sizeof(int *));
    int *ptr = (int *)(single_arr + M);
    for (int i = 0; i < M; i++) single_arr[i] = ptr + N * i;
    if (input(single_arr, M, N)) {
        exit(0);
    }
    output(single_arr, M, N);
    str_max(single_arr, M, N);
    colomn_min(single_arr, M, N);
    free(single_arr);
}

void statik(int M, int N) {
    int data[M][N];
    int *ptr[M];
    for (int i = 0; i < M; i++) {
        ptr[i] = data[i];
    }
    if (input(ptr, M, N)) {
        exit(0);
    }
    output(ptr, M, N);
    str_max(ptr, M, N);
    colomn_min(ptr, M, N);
}

int input(int **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &a[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    }
    return 0;
}

void output(int **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            printf("%d ", a[i][j]);
        }
        printf("%d\n", a[i][m - 1]);
    }
}

void str_max(int **a, int n, int m) {
    int max[n];
    int maxx;
    for (int i = 0; i < n; i++) {
        maxx = a[i][0];
        for (int j = 0; j < m; j++) {
            if (a[i][j] > maxx) {
                maxx = a[i][j];
            }
        }
        max[i] = maxx;
    }
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", max[i]);
    }
    printf("%d\n", max[n - 1]);
}

void colomn_min(int **a, int n, int m) {
    int min[m];
    int minn;
    for (int i = 0; i < m; i++) {
        minn = a[0][i];
        for (int j = 0; j < n; j++) {
            if (a[j][i] < minn) {
                minn = a[j][i];
            }
        }
        min[i] = minn;
    }
    for (int i = 0; i < m - 1; i++) {
        printf("%d ", min[i]);
    }
    printf("%d", min[m - 1]);
}
