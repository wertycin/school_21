/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>
#define NMAX 10
int input(int *a, int *n);
void output(int *a, int n, int sum);
int sum_numbers(int *a, int n, int *flag);
int find_numbers(int *a, int n, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int n, data[NMAX];     // Исходный массив
    int l, numbers[NMAX];  // Новый массив
    int sum_2k;            // Сумма всех четных элементов
    int flag = 1;
    if (input(data, &n)) {
        return 0;
    }
    sum_2k = sum_numbers(data, n, &flag);
    if (flag) {
        printf("n/a");
        return 0;
    }
    l = find_numbers(data, n, sum_2k, numbers);
    output(numbers, l, sum_2k);
    return 0;
}
/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *a, int n, int *flag) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0 && a[i] % 2 == 0) {
            sum = sum + a[i];
            *flag = 0;
        }
    }

    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *a, int n, int number, int *numbers) {
    int length = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0 && number % a[i] == 0) {
            numbers[length] = a[i];
            length++;
        }
    }
    return length;
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

void output(int *a, int n, int sum) {
    printf("%d\n", sum);
    for (int *p = a; p - a < n - 1; p++) {
        printf("%d ", *p);
    }
    printf("%d", a[n - 1]);
}
