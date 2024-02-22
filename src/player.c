#include "player.h"

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