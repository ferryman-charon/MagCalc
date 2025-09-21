#include "draw_molecules.h"

double get_deltaE(const Spins *s, int i);
double get_total_energy(const Spins *s);

bool grid_new(Spins **spins) {
    *spins = calloc(1, sizeof(Spins));

    if (*spins == NULL) {
        fprintf(stderr, "Failed creating spins!\n");
        return false;
    }
    Spins *s = *spins;
    

    s->grid = calloc(GRID_HEIGHT*GRID_WIDTH, sizeof(int));
    if (!s->grid) {
        free(s);
        *spins = NULL;
        fprintf(stderr, "Error allocating memory for calc grid: %s\n", SDL_GetError());
        return false;
    }

    s->h = GRID_HEIGHT;
    s->w = GRID_WIDTH;
    s->size = GRID_HEIGHT * GRID_WIDTH;
    
    s->Temperature = TEMPERATURE;
    s->J = COHESIVE_STRENGTH;

    return true;

}
void grid_free(Spins **spins) {
    if (*spins) {
        Spins *s = *spins;

        if (s->grid) {
            free(s->grid);
            s->grid = NULL;
        }

        free(s);
        *spins = NULL;
    }
}

void grid_reset_values(Spins *s) {
    for (size_t i = 0; i < (s->size); i++) {
        if (rand()%4 == 1)
            s->grid[i] = 1;
        else
            s->grid[i] = -1;
    }
    s->energy = get_total_energy(s);
}

void update_grid(Spins *s) {
    int i = rand() % s->size;
    double dE = get_deltaE(s, i);

    printf("%f\n", s->energy);
    if (dE <= 0.0) {
        s->grid[i] *= - 1;
        s->energy += dE;
    } else {
        double u = (double)rand() / (double)RAND_MAX;
        double boltz = exp(-dE / s->Temperature);
        if (u < boltz) {
            s->grid[i] *= -1;
            s->energy += dE;
        }
    }
}

double get_total_energy(const Spins *s) {
    double E = 0.0;
    for (int y = 0; y < s->h; y++) {
        for (int x = 0; x < s->w; x++) {
            int i = y * s->w + x;
            int sigma = s->grid[i];
            if (x < s->w - 1)
                E -= s->J * sigma * s->grid[i + 1];
            if (y < s->h - 1)
                E -= s->J * sigma * s->grid[i + s->w];
        }
    }
    return E;
}

double get_deltaE(const Spins *s, int i) {

    int x = i % s->w;
    int y = i / s->w;
    int sigma = s->grid[i];

    int sum_neighbors = 0;
    if (x > 0) sum_neighbors += s->grid[i - 1];
    if (x < s->w - 1) sum_neighbors += s->grid[i + 1];
    if (y > 0) sum_neighbors += s->grid[i - s->w];
    if (y < s->h - 1) sum_neighbors += s->grid[i + s->w];

    double dE = 2.0 * s->J * sigma * sum_neighbors;
    return dE;
}