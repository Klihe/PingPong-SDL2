#include "ball.h"

void drawBall(SDL_Renderer* renderer, Ball* ball) {
    SDL_SetRenderDrawColor(renderer, ball->color.r, ball->color.g, ball->color.b, ball->color.a);
    SDL_RenderFillRect(renderer, &ball->rect);
}

void moveBall(Ball* ball) {
    if (ball->rect.x < 0 || ball->rect.x > WINDOW_WIDTH - ball->rect.w) {
        ball->rect.x = WINDOW_WIDTH/2 - ball->rect.w/2;
        ball->rect.y = WINDOW_HEIGHT/2 - ball->rect.h/2;
        ball->speed = -ball->speed;
    }
    else if (ball->rect.y < 0 || ball->rect.y > WINDOW_HEIGHT - ball->rect.h) {
        ball->angle = 360 - ball->angle;
    }
    ball->rect.x += (int)(ball->speed * cos((double)ball->angle * M_PI / 180));
    ball->rect.y += (int)(ball->speed * sin((double)ball->angle * M_PI / 180));
}