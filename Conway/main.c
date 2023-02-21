#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define ROWS 60
#define COLUMNS 50
#define CELLSIZE 20


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

void calculate(int** board, SDL_Renderer* renderer){
    for (int j=0; j < ROWS; j++){
        for (int i=0; i < COLUMNS; i++){
            int neighbours = 0;
            neighbours = detect_collision(board, i, j);
            if (neighbours == 3) { board[i][j] = 1; }
            if (neighbours > 3 || neighbours < 2) { board[i][j] = 0; }

            if (board[i][j] == 1){
                SDL_Rect r; 
                r.x = j*CELLSIZE;
                r.y = i*CELLSIZE;
                r.w = CELLSIZE-1;
                r.h = CELLSIZE-1;
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &r);
            }
        }
    }
}

int main(void){
    SDL_Window* window;
    window = SDL_CreateWindow("Testando", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    // setup renderer
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int **board;
    board = generate_map();

    SDL_Event event;
    bool running = true;
    while (running){
        unsigned int start = SDL_GetPerformanceCounter();
        SDL_RenderClear(renderer);
        calculate(board, renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        //Events Loop -- Returns 0 if no events
        while(SDL_PollEvent(&event)){
            switch( event.type ){
                case SDL_KEYDOWN:
                    if (SDLK_q){ running = false; }
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        unsigned int end = SDL_GetPerformanceCounter();
        unsigned int elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(16.666f - elapsedMS));
    }
    free(board);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
