#include <stdio.h>
#include <stdlib.h>

int input(int **a, int n, int m);
void output(int **a, int n, int m);
void simplest(int n, int m);
void medium(int M, int N);
void hardest(int M, int N);
void statik(int M, int N);

int main() {
    int n, m, choose;
    char c;
    if (scanf("%d%c", &choose, &c) != 2 || c != '\n' || choose < 1 || choose > 4) {
        printf("n/a");
        return 0;
    }
    if (scanf("%d %d%c", &n, &m, &c) != 3 || c != '\n' || n < 1 || m < 1) {
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
}

int input(int **a, int n, int m) {
    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((j != m - 1 && (scanf("%d%c", &a[i][j], &c) != 2 || c != ' ')) ||
                (j == m - 1 && ((scanf("%d%c", &a[i][j], &c) != 2 || (c != '\n' && c != EOF))))) {
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
        if (i < n - 1)
            printf("%d\n", a[i][m - 1]);
        else
            printf("%d", a[i][m - 1]);
    }
}
