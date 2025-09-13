#ifndef DRAW_MOLECULES_H
#define DRAW_MOLECULES_H

#include "main.h"

#define GRID_WIDTH (WINDOW_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (WINDOW_HEIGHT / CELL_SIZE)

#define GRID_SIZE (GRID_WIDTH * GRID_HEIGHT)

void init_grid(bool *grid);
void update_grid(bool *grid);

#endif