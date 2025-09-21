#ifndef DRAW_MOLECULES_H
#define DRAW_MOLECULES_H

#include "main.h"

#define GRID_WIDTH (WINDOW_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (WINDOW_HEIGHT / CELL_SIZE)

typedef struct {
    int h, w, size;
    double Temperature, mu, J, energy;
    int *grid;
} Spins;

bool grid_new(Spins **spins);
void grid_free(Spins **spins);
void grid_reset_values(Spins *s);

void update_grid(Spins *s);

#endif