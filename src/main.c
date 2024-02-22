#include <SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "config.h"
#include "player.h"
#include "ball.h"

int main() {
    srand(time(NULL));
    int rand_num = rand();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Player player1 = {{0, WINDOW_HEIGHT/2 - 120/2, 30, 120}, {255, 0, 0, 255}, SDL_SCANCODE_W, SDL_SCANCODE_S, 5};
    Player player2 = {{WINDOW_WIDTH - 30, WINDOW_HEIGHT/2 - 120/2, 30, 120}, {0, 255, 0, 255}, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, 5};
    Ball ball = {{WINDOW_WIDTH/2 - 10/2, WINDOW_HEIGHT/2 - 10/2, 10, 10}, {0, 0, 255, 255}, 50, 45};

    SDL_Event event;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderClear(renderer);

        drawPlayer(renderer, &player1);
        drawPlayer(renderer, &player2);
        drawBall(renderer, &ball);

        movePlayer(state, &player1);
        movePlayer(state, &player2);
        moveBall(&ball, rand_num);
        printf("Ball speed: %d\n", ball.speed);

        checkCollisionBall(&ball, &player1.rect, &player2.rect, rand_num);
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}