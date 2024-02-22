#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "config.h"

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    SDL_Scancode upKey;
    SDL_Scancode downKey;
    int speed;
} Player;

void drawPlayer(SDL_Renderer* renderer, Player* player);
void movePlayer(const Uint8* state, Player* player);

#endif /* PLAYER_H */
