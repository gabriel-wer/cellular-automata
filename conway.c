#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#define ROWS 10
#define COLUMNS 5
#define DEAD "."
#define ALIVE "O"


int **generate_map(){
    int **map;
    map = malloc(sizeof(int *) * ROWS);
    srand(time(0));
    for (int i=0; i < ROWS; i++){
        map[i] = malloc(sizeof(int *) * COLUMNS);
        for (int j=0; j < COLUMNS; j++){ map[i][j] = rand() % 2; }
    }
    return map;
}

int detect_collision(int** board, int i, int j){
    int count = 0;
    for (int x=i-1; x<=i+1; x++){
        for (int y=j-1; y<=j+1; y++){
            // check for out of bounds
            if (x < 0 || x >= COLUMNS) { continue; }
            if (y < 0 || y>= ROWS) { continue; }
            
            //skip own cell
            if (x == i && y == j) { continue; }

            //count neighbours
            if (board[x][y] == 1) { count += 1; }
        }
    }
    return count;
}

void calculate(int** board){
    for (int j=0; j < ROWS; j++){
        for (int i=0; i < COLUMNS; i++){
            int neighbours = 0;
            neighbours = detect_collision(board, i, j);
            if (neighbours == 3) { board[i][j] = 1; }
            if (neighbours > 3 || neighbours < 2) { board[i][j] = 0; }

            if (board[i][j] == 1){ printf("%s", ALIVE); }
            if (board[i][j] == 0){ printf("%s", DEAD); }
        }
        printf("\n");
    }
}

int main(void){
    int **board;
    board = generate_map();
    bool running = true;
    while (running){
        calculate(board);
        sleep(1);
        system("clear");
    }
    free(board);
    return 0;
}
