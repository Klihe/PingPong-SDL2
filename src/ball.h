#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <math.h>
#include "config.h"

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    int speed;
    int angle;
} Ball;

void drawBall(SDL_Renderer* renderer, Ball* ball);
void moveBall(Ball* ball);

#endif