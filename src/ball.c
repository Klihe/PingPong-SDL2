#include "ball.h"

void drawBall(SDL_Renderer* renderer, Ball* ball) {
    SDL_SetRenderDrawColor(renderer, ball->color.r, ball->color.g, ball->color.b, ball->color.a);
    SDL_RenderFillRect(renderer, &ball->rect);
}

void resetBall(Ball* ball, int rand) {
    ball->rect.x = WINDOW_WIDTH/2 - ball->rect.w/2;
    ball->rect.y = WINDOW_HEIGHT/2 - ball->rect.h/2;
    ball->speed = 50;
    ball->angle = rand % 360;
}

void moveBall(Ball* ball, int rand) {
    if (ball->rect.x < 0 || ball->rect.x > WINDOW_WIDTH - ball->rect.w) {
        resetBall(ball, rand);
    }
    else if (ball->rect.y < 0 || ball->rect.y > WINDOW_HEIGHT - ball->rect.h) {
        ball->angle = -ball->angle - rand % 10;
        ball->speed += 2;
    }
    ball->rect.x += (int)((ball->speed)/10 * cos((double)ball->angle * M_PI / 360));
    ball->rect.y += (int)((ball->speed)/10 * sin((double)ball->angle * M_PI / 360));
}

bool checkCollisionBall(Ball* ball, SDL_Rect* rect1, SDL_Rect* rect2, int rand) {
    if (SDL_HasIntersection(&ball->rect, rect1) || SDL_HasIntersection(&ball->rect, rect2)) {
        ball->angle = 360 -ball->angle - rand % 30;
        ball->speed += 5;
        return true;
    }
    return false;
}