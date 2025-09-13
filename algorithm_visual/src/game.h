#ifndef GAME_H
#define GAME_H

#include "main.h"
#define PITCH (WINDOW_WIDTH * sizeof(uint32_t))

struct Game {
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *out_screen;
        SDL_Event event;
        uint32_t pixels;
        bool is_running;
        bool *molecule_grid;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
void game_run(struct Game *g);

#endif