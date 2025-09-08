#ifndef EVENTS_H
#define EVENTS_H

#include "game.h"

typedef uint32_t (*ColorFunc)(double f);
void game_events(struct Game *g);
void game_update_pixels(struct Game *g);
void game_init_pixels(struct Game *g);

#endif