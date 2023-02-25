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


void generate_map(int *map){
    srand(time(0));
    for (int i=0; i < COLUMNS; i++){
        for (int j=0; j < ROWS; j++){ 
            map[i * ROWS + j] = rand() % 2; 
        }
    }
}

void detect_collision(int *board, int i, int j){
    int count = 0;
    for (int x=i-1; x<=i+1; x++){
        for (int y=j-1; y<=j+1; y++){
            // check for out of bounds
            if (x < 0 || x >= COLUMNS) { continue; }
            if (y < 0 || y>= ROWS) { continue; }
            
            //skip own cell
            if (x == i && y == j) { continue; }

            //count neighbours
            if (board[x * ROWS + y] == 1) { 
                count += 1; 
            }
        }
    }
    if (count == 3) { board[i * ROWS + j] = 1; }
    if (count > 3 || count < 2) { board[i * ROWS + j] = 0; }
}

int main(void){
    SDL_Window* window;
    window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CELLSIZE*ROWS, CELLSIZE*COLUMNS, SDL_WINDOW_SHOWN);

    // setup renderer
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int *board = malloc((COLUMNS * ROWS) * sizeof(int));
    generate_map(board);

    SDL_Event event;
    bool running = true;
    while (running){
        SDL_RenderClear(renderer);
        for (int i=0; i < COLUMNS; i++){
            for (int j=0; j < ROWS; j++){
                detect_collision(board, i, j);
                if (board[i * ROWS + j] == 1){
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
        SDL_Delay(100);
    }
    free(board);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
