#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "draw_molecules.h"

#define PITCH (WINDOW_WIDTH * sizeof(uint32_t))

struct Game {
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *out_screen;
        SDL_Event event;
        bool is_running;
        Spins *molecule_grid;
        uint32_t *pixels;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
void game_run(struct Game *g);

#endif