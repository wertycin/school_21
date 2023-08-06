#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// COLORS
// 40    черный
// 41    красный
// 42    зеленый
// 43    желтый
// 44    синий
// 45    пурпурный
// 46    голубой
// 47    белый
#define HEIGHT 25
#define WIDTH 80
#define ARCH 100
#define ALIVE_I '*'
#define DEAD_I '-'
#define ALIVE_O ' '
#define DEAD_O ' '
#define BORDER ' '
#define RESET "\x1b[0m"
#define ALIVE_C "\x1b[30m"
#define DEAD_C "\x1b[30m"
#define BORDER_C "\x1b[30m"
#define BACKGROUND_A "\x1b[44m"
#define BACKGROUND_D "\x1b[0m"
#define BACKGROUND_B "\x1b[47m"
#define PAUSE 1000000
#define MAX_FILE_NAME 100

void initial_plato(int plato[HEIGHT][WIDTH], FILE* file);
void game_start(FILE* file, int speed);
void print(int plato[HEIGHT][WIDTH]);
void plato_update(int plato[HEIGHT][WIDTH]);
int cell_update(int plato[HEIGHT][WIDTH], int x, int y, int old_status);
void record_plato(int plato[HEIGHT][WIDTH], int archive[ARCH][HEIGHT][WIDTH], int *count);
int game_end(int plato[HEIGHT][WIDTH], int archive[ARCH][HEIGHT][WIDTH]);

int main() {
    char file_name[MAX_FILE_NAME];
    int speed;
    printf("Choose game speed (1 - min, 10 - max): ");
    if (scanf("%d", &speed) != 1 || speed < 1 || speed > 10) {
        printf("Incorrect speed");
        exit(0);
    };
    printf("Select file to play: ");
    scanf("%s", file_name);
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Incorrect filename");
        exit(0);
    }
    game_start(file, speed);
    fclose(file);
    return 0;
}

void game_start(FILE* file, int speed) {
    int count = 0;
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
    while (game_end(plato, archive)) {
        printf("\e[1;1H\e[2J");
        print(plato);
        record_plato(plato, archive, &count);
        plato_update(plato);
        usleep(PAUSE / speed);
    }
    printf("\e[1;1H\e[2J");
    print(plato);
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
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("%s%s%c%s", BACKGROUND_B, BORDER_C, BORDER, RESET);
    }
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s%s%c%s", BACKGROUND_B, BORDER_C, BORDER, RESET);
        for (int j = 0; j < WIDTH; j++) {
            if (plato[i][j])
                printf("%s%s%c%s", BACKGROUND_A, ALIVE_C, ALIVE_O, RESET);
            else
                printf("%s%s%c%s", BACKGROUND_D, DEAD_C, DEAD_O, RESET);
        }
        printf("%s%s%c%c%s", BACKGROUND_B, BORDER_C, BORDER, '\n', RESET);
    }
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("%s%s%c%s", BACKGROUND_B, BORDER_C, BORDER, RESET);
    }
    printf("\n");
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

void record_plato(int plato[HEIGHT][WIDTH], int archive[ARCH][HEIGHT][WIDTH], int *count) {
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
