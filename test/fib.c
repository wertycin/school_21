#include <stdio.h>

int fib(int n);

int main() {
    // int n;
    // scanf("%d", &n);
    for (int i = 1; i < 100; i++) printf("%d ", fib(i));
    return 0;
}

int fib(int n) {
    int a = 1, b = 1;
    int tmp;
    for (int i = 0; i < n - 2; i++) {
        tmp = a;
        a += b;
        b = tmp;
    }
    return a;
}