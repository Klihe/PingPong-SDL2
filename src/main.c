#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    SDL_Scancode upKey;
    SDL_Scancode downKey;
    int speed;
} Player;

void drawPlayer(SDL_Renderer* renderer, Player* player) {
    SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
    SDL_RenderFillRect(renderer, &player->rect);
}

void movePlayer(const Uint8* state, Player* player) {
    if (state[player->upKey] && player->rect.y > 0) {
        player->rect.y -= player->speed;
    }
    if (state[player->downKey] && player->rect.y < WINDOW_HEIGHT - player->rect.h) {
        player->rect.y += player->speed;
    }
}

int main() {
    printf("Hello, SDL!\n");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Player player1 = {{100, 100, 50, 50}, {255, 0, 0, 255}, SDL_SCANCODE_W, SDL_SCANCODE_S, 5};
    Player player2 = {{200, 200, 50, 50}, {0, 255, 0, 255}, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, 5};

    SDL_Event event;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // Set render color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Clear the window with the render color
        SDL_RenderClear(renderer);

        drawPlayer(renderer, &player1);
        drawPlayer(renderer, &player2);

        movePlayer(state, &player1);
        movePlayer(state, &player2);
        
        // Update the screen
        SDL_RenderPresent(renderer);

    }

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}