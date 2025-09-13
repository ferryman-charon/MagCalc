#ifndef MAIN_H
#define MAIN_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#define WINDOW_TITLE "Monte Carlo"
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000

#define COLOR_BLACK (SDL_Color){0,0,0,255}
#define COLOR_WHITE (SDL_Color){255,255,255,255}
#define COLOR_BLUE (SDL_Color){0,0,255,255}

#define CELL_SIZE 20

#define TEMPERATURE 2.5
#define CHEMICAL_POTENTIAL -2.0
#define COHESIVE_STRENGTH 1

#define SDL_COLOR_TO_ARGB32(col) \
    ( ((Uint32)(col).a << 24) | ((Uint32)(col).r << 16) | ((Uint32)(col).g << 8) | ((Uint32)(col).b) )

#endif