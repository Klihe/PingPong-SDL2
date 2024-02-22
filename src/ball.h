#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <stdbool.h>
#include <math.h>
#include "config.h"

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    int speed;
    int angle;
} Ball;

void drawBall(SDL_Renderer* renderer, Ball* ball);
void resetBall(Ball* ball, int rand);
void moveBall(Ball* ball, int rand);
bool checkCollisionBall(Ball* ball, SDL_Rect* rect1, SDL_Rect* rect2, int rand);

#endif