#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

//Константы
#define HEIGHt 25             // Высота
#define WIDTH 80              // Ширина
#define RACKET_1_X 2          // Координата X левой ракетки
#define RACKET_2_X 77         // Координата X правой ракетки
#define STARTING_BALL_X 38    // Координа X шара в начале раунда
#define STARTING_BALL_Y 12    // Координа Y шара в начале раунда
#define STARTING_RACKET_Y 13  // Координа Y ракеток в начале раунда

#define ABS(a) (((a) < 0) ? -(a) : (a))  // Макрос модуля

void game();  // Звпускает игру и печатает победителя!

void polygon(int ball_x, int ball_y, int racket_1_y, int racket_2_y, int res);  // Рисует поле игры

// char reading_command(int i, char a, char b);  //Считываем команду первого игрока

// Запускает раунд игры и возвращает общий счет
int read_1(int ball_x, int ball_y, int racket_1_y, int racket_2_y, int res);

// Возвращает новые координаты шара, в зависимости от параметра возвращает x или y
int chang_coord_ball(int x, int y, int racket_1_y, int racket_2_y, char x_or_y);

// Возвращает новое расположение рактки в зависимости от флага и номера ракетки
int moving_racket(int y, char flag, int i);

int check_result(int ball_x);  // Возвращает информацию об окончании игры

int main() {
    game();
    return 0;
}

void game() {
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    int res = 0;
    int flag = 1;
    while (res / 100 != 21 && res % 100 != 21) {
        int res1, res2;
        res1 = res / 100;
        res2 = res % 100;
        polygon(STARTING_BALL_X, STARTING_BALL_Y, STARTING_RACKET_Y, STARTING_RACKET_Y, res);
        printw("%36c%02d:%02d\n", ' ', res1, res2);
        if (flag)
            res = read_1(STARTING_BALL_X, STARTING_BALL_Y, STARTING_RACKET_Y, STARTING_RACKET_Y, res);
        else
            res = read_1(-STARTING_BALL_X, STARTING_BALL_Y, STARTING_RACKET_Y, STARTING_RACKET_Y, res);
        if (res / 100 != res1) {
            flag = 0;
        } else {
            flag = 1;
        }
    }
    endwin();
    if (res / 100 == 21) {
        printf("Good game! Player 1 won! Score is %02d:%02d\n", res / 100, res % 100);
    } else {
        printf("Good game! Player 2 won! Score is %02d:%02d\n", res / 100, res % 100);
    }
}

void polygon(int ball_x, int ball_y, int racket_1_y, int racket_2_y, int res) {
    usleep(100000);
    clear();
    int res1 = res / 100;
    int res2 = res % 100;
    for (int i = 0; i < HEIGHt; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || j == 0 || i == HEIGHt - 1 || j == WIDTH - 1) {  // отрисовка границ
                printw("^");
            } else if (i == ball_y && j == ball_x) {  // отрисовка шара
                printw("*");
            } else if ((i == racket_1_y || i == racket_1_y - 1 || i == racket_1_y - 2) &&
                       j == 2) {  // отрисовка первой ракетки
                printw("#");
            } else if ((i == racket_2_y || i == racket_2_y - 1 || i == racket_2_y - 2) &&
                       j == WIDTH - 3) {  // отрисовка второй ракетки
                printw("#");
            } else if (j == STARTING_BALL_X) {
                printw("|");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
    printw("%36c%02d:%02d\n", ' ', res1, res2);
    refresh();
}

int read_1(int ball_x, int ball_y, int racket_1_y, int racket_2_y, int res) {
    int flag = 0;  // flag, показывающий результат раунда

    int res1 = res / 100;  // очки первого игрока
    int res2 = res % 100;  // очки второго игрока

    while (flag == 0) {  // цикл раунда

        char step_1;  // Для команды первой ракетки

        char buf;  // буферная переменная

        // Считываем команду первого игрока
        // usleep(50000);
        step_1 = getch();

        // Меняем расположение ракеток

        racket_1_y = moving_racket(racket_1_y, step_1, 1);
        racket_2_y = moving_racket(racket_2_y, step_1, 2);

        // Меняем расположение мяча
        buf = ball_x;
        ball_x = chang_coord_ball(ball_x, ball_y, racket_1_y, racket_2_y, 'x');
        ball_y = chang_coord_ball(buf, ball_y, racket_1_y, racket_2_y, 'y');

        // Рисуем поле
        polygon(ABS(ball_x), ABS(ball_y), racket_1_y, racket_2_y, res);

        // печать счета

        //Проверка на результат раунда
        flag = check_result(ball_x);
    }

    if (flag == -1) {
        res2++;
    } else {
        res1++;
    }

    res = res1 * 100 + res2;

    //Возвращаем общий счет
    return res;
}

int chang_coord_ball(int x, int y, int racket_1_y, int racket_2_y, char x_or_y) {
    int res, v_x = 1, v_y = 1;  //определяем скорость
    if (x < 0) v_x = -1;
    x = ABS(x);
    if (y < 0) v_y = -1;
    y = ABS(y);
    if (y + v_y == 0 || y + v_y == 24) {
        v_y = -v_y;
        if (x + v_x == RACKET_1_X + 1 &&
            (racket_1_y == y + v_y || racket_1_y - 1 == y + v_y || racket_1_y - 2 == y + v_y))
            x = x + 2 * v_x;
        if (x_or_y == 'x')
            res = x * v_x;
        else
            res = y * v_y;
    } else {
        if (x + v_x == RACKET_1_X) {  //левая
            if (x + v_x == RACKET_1_X + 1 &&
                (racket_1_y == y + v_y || racket_1_y - 1 == y + v_y || racket_1_y - 2 == y + v_y)) {
                v_x = -v_x;
                y = y + 2 * v_y;
            } else if (racket_1_y == y + v_y || racket_1_y - 1 == y + v_y || racket_1_y - 2 == y + v_y) {
                v_x = -v_x;
            } else {
                x = x + v_x;
                y = y + v_y;
            }
        } else if (x + v_x == RACKET_2_X) {  // правая
            if (x + v_x == RACKET_2_X + 1 &&
                (racket_2_y == y + v_y || racket_2_y - 1 == y + v_y || racket_2_y - 2 == y + v_y)) {
                v_x = -v_x;
                y = y + 2 * v_y;
            } else if (racket_2_y == y + v_y || racket_2_y - 1 == y + v_y || racket_2_y - 2 == y + v_y) {
                v_x = -v_x;
            } else {
                x = x + v_x;
                y = y + v_y;
            }
        } else {
            x = x + v_x;
            y = y + v_y;
        }
        if (x_or_y == 'x') {
            res = x * v_x;
        } else {
            res = y * v_y;
        }
    }
    return res;
}

int moving_racket(int y, char flag, int i) {
    char up, down;
    if (i == 1) {
        up = 'a';
        down = 'z';

    } else if (i == 2) {
        up = 'k';
        down = 'm';
    }

    if (flag == up && y > 3) {
        --y;
    }
    if (flag == down && y < 23) {
        ++y;
    }
    return y;
}

int check_result(int ball_x) {
    int res = 0;
    if (ball_x == 0) {
        res = -1;
    } else if (ball_x == WIDTH - 1) {
        res = 1;
    }
    return res;
}
