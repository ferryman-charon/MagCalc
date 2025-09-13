#include "draw_molecules.h"


void init_grid(bool *grid) {
    for (size_t i = 0; i < GRID_SIZE; i++) {
        grid[i] = (bool)(rand()%2 == 1);
    }
}

void update_grid(bool *grid) {
    size_t i1 = rand()%GRID_SIZE;
    size_t i2 = rand()%GRID_SIZE;

    if (grid[i1] != grid[i2]) {
        bool temp = grid[i1];
        grid[i1] = grid[i2];
        grid[i2] = temp;
    }
}

size_t get_grid_energy(bool *grid) {
    return 1;
}
