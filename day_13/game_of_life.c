#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 25
#define WIDTH 80
#define ARCH 100
#define ALIVE '*'
#define DEAD '-'
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"
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
    printf("Choose game speed (1 - min, 5 - max): ");
    scanf("%d", &speed);
    speed = PAUSE / speed;
    printf("Select file to play: ");
    scanf("%s", file_name);
    FILE *file;
    file = fopen(file_name, "r");
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
        usleep(speed);
    }
    print(plato);
}

void initial_plato(int plato[HEIGHT][WIDTH], FILE* file) {
    char c;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (fscanf(file, "%c", &c) != 1 || (c != ALIVE && c != DEAD)) {
                printf("Error!%c is incorrect input!\n", c);
                exit(0);
            };
            if (c == ALIVE) {
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
        printf("%s%c%s", RED, '.', RESET);
    }
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s%c%s", RED, '.', RESET);
        for (int j = 0; j < WIDTH; j++) {
            if (plato[i][j])
                printf("%s%c%s", GREEN, '*', RESET);
            else
                printf(" ");
        }
        printf("%s%s%s", RED, ".\n", RESET);
    }
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("%s%c%s", RED, '.', RESET);
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

