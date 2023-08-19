#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// COLORS
// 0    черный
// 1    красный
// 2    зеленый
// 3    желтый
// 4    синий
// 5    пурпурный
// 6    голубой
// 7    белый
#define HEIGHT 25
#define WIDTH 80
#define ARCH 100
#define ALIVE_I '*'
#define DEAD_I '-'
#define ALIVE_O '0'
#define DEAD_O '+'
#define BORDER ' '
#define RESET 0
#define ALIVE_C 2
#define DEAD_C 1
#define BORDER_C 0
#define BACKGROUND_A 0
#define BACKGROUND_D 0
#define BACKGROUND_B 0
#define PAUSE 1000000
#define MAX_SPEED 10
#define MIN_SPEED 1

void initial_plato(int plato[HEIGHT][WIDTH], FILE* file);
void game_start(FILE* file, int speed);
void print(int plato[HEIGHT][WIDTH]);
void plato_update(int plato[HEIGHT][WIDTH]);
int cell_update(int plato[HEIGHT][WIDTH], int x, int y, int old_status);
void record_plato(int plato[HEIGHT][WIDTH], int archive[ARCH][HEIGHT][WIDTH], int* count);
int game_end(int plato[HEIGHT][WIDTH], int archive[ARCH][HEIGHT][WIDTH]);

int main() {
    char file_name[100];
    int speed;
    printf("Choose game speed (1 - min, 10 - max): ");
    if (scanf("%d", &speed) != 1 || speed < MIN_SPEED || speed > MAX_SPEED) {
        printf("Incorrect speed");
        exit(0);
    };
    printf("Select file to play: ");
    scanf("%99s", file_name);
    FILE* file;
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Incorrect filename");
        exit(0);
    }
    game_start(file, speed);
    fclose(file);
    printf("Game over!\n");
    return 0;
}

void game_start(FILE* file, int speed) {
    int count = 0;
    char c = 'a';
    int plato[HEIGHT][WIDTH];
    int archive[ARCH][HEIGHT][WIDTH];
    for (int a = 0; a < ARCH; a++) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                archive[a][i][j] = 0;
            }
        }
    }
    initial_plato(plato, file);
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, ALIVE_C, BACKGROUND_A);
    init_pair(2, DEAD_C, BACKGROUND_D);
    init_pair(3, BORDER_C, BACKGROUND_B);
    while (game_end(plato, archive) && c != 'z') {
        c = getch();
        if (c == 'w' && speed < MAX_SPEED) {
            speed++;
        }
        if (c == 's' && speed > MIN_SPEED) {
            speed--;
        }
        print(plato);
        record_plato(plato, archive, &count);
        plato_update(plato);
        usleep(PAUSE / speed);
        fflush(stdout);
    }
    print(plato);
    usleep(PAUSE * 3);
    endwin();
}

void initial_plato(int plato[HEIGHT][WIDTH], FILE* file) {
    char c;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (fscanf(file, "%c", &c) != 1 || (c != ALIVE_I && c != DEAD_I)) {
                printf("Error!%c is incorrect input!\n", c);
                exit(0);
            };
            if (c == ALIVE_I) {
                plato[i][j] = 1;
            } else
                plato[i][j] = 0;
        }

        if ((fscanf(file, "%c", &c) != 1 || c != '\n') && (i < HEIGHT - 1)) {
            printf("Error!%c is incorrect input!\n", c);
            exit(0);
        }
    };
}

void print(int plato[HEIGHT][WIDTH]) {
    clear();
    for (int i = 0; i < WIDTH + 2; i++) {
        attron(COLOR_PAIR(3));
        printw("%c", BORDER);
        attroff(COLOR_PAIR(3));
    }
    printw("\n");
    for (int i = 0; i < HEIGHT; i++) {
        attron(COLOR_PAIR(3));
        printw("%c", BORDER);
        attroff(COLOR_PAIR(3));
        for (int j = 0; j < WIDTH; j++) {
            if (plato[i][j]) {
                attron(COLOR_PAIR(1));
                printw("%c", ALIVE_O);
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                printw("%c", DEAD_O);
                attroff(COLOR_PAIR(2));
            }
        }
        attron(COLOR_PAIR(3));
        printw("%c%c", BORDER, '\n');
        attroff(COLOR_PAIR(3));
    }
    for (int i = 0; i < WIDTH + 2; i++) {
        attron(COLOR_PAIR(3));
        printw("%c", BORDER);
        attroff(COLOR_PAIR(3));
    }
    printw("\n");
    refresh();
}

void plato_update(int plato[HEIGHT][WIDTH]) {
    int old[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            old[i][j] = plato[i][j];
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            plato[i][j] = cell_update(old, j, i, old[i][j]);
        }
    }
}

int cell_update(int plato[HEIGHT][WIDTH], int x, int y, int old_status) {
    int sum = 0;
    int new_status = 0;
    for (int i = y - 1; i < y + 2; i++) {
        for (int j = x - 1; j < x + 2; j++) {
            sum += plato[(i + HEIGHT) % HEIGHT][(j + WIDTH) % WIDTH];
        }
    }
    sum -= plato[y][x];
    if (old_status) {
        if (sum == 2 || sum == 3) new_status = 1;
    } else {
        if (sum == 3) new_status = 1;
    }
    return new_status;
}

void record_plato(int plato[HEIGHT][WIDTH], int archive[ARCH][HEIGHT][WIDTH], int* count) {
    if (*count >= ARCH) *count = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            archive[*count][i][j] = plato[i][j];
        }
    }
    *count = *count + 1;
}

int game_end(int plato[HEIGHT][WIDTH], int archive[ARCH][HEIGHT][WIDTH]) {
    int cycling;
    for (int a = 0; a < ARCH; a++) {
        cycling = 0;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (plato[i][j] != archive[a][i][j]) {
                    cycling = 1;
                }
            }
        }
        if (!cycling) break;
    }
    return cycling;
}
