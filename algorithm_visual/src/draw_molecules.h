#ifndef DRAW_MOLECULES_H
#define DRAW_MOLECULES_H

#include "main.h"

#define GRID_WIDTH (WINDOW_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (WINDOW_HEIGHT / CELL_SIZE)


typedef struct {
    size_t h, w, size;
    double Temperature, mu, J, energy;
    bool *grid, *seen;
} Molecules;

bool grid_new(Molecules **molecules);
void grid_free(Molecules **molecules);
void grid_reset_values(Molecules *m);

void update_grid(Molecules *m);

#endif