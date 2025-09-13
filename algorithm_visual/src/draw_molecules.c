#include "draw_molecules.h"

int get_deltaE(const Molecules *m, int index);
size_t get_grid_energy(const Molecules *m);
double get_physical_energy(const Molecules *m);

bool grid_new(Molecules **molecules) {
    *molecules = calloc(1, sizeof(Molecules));

    if (*molecules == NULL) {
        fprintf(stderr, "Failed creating molecules!\n");
        return false;
    }
    Molecules *m = *molecules;
    

    m->grid = calloc(GRID_HEIGHT*GRID_WIDTH, sizeof(bool));
    if (!m->grid) {
        free(m);
        *molecules = NULL;
        fprintf(stderr, "Error allocating memory for calc grid: %s\n", SDL_GetError());
        return false;
    }
    
    m->seen = calloc(GRID_HEIGHT*GRID_WIDTH, sizeof(bool));
    if (!m->seen) {
        free(m->grid);
        m->grid = NULL;

        free(m);
        *molecules = NULL;
        fprintf(stderr, "Error allocating memory for calc grid: %s\n", SDL_GetError());
        return false;
    }

    m->h = GRID_HEIGHT;
    m->w = GRID_WIDTH;
    m->size = GRID_HEIGHT * GRID_WIDTH;
    
    m->Temperature = TEMPERATURE;
    m->mu = CHEMICAL_POTENTIAL;
    m->J = COHESIVE_STRENGTH;

    return true;

}
void grid_free(Molecules **molecules) {
    if (*molecules) {
        Molecules *m = *molecules;

        if (m->seen) {
            free(m->seen);
            m->seen = NULL;
        }

        if (m->grid) {
            free(m->grid);
            m->grid = NULL;
        }

        free(m);
        *molecules = NULL;
    }
}

void grid_reset_values(Molecules *m) {
    for (size_t i = 0; i < (m->size); i++) {
        m->grid[i] = (bool)(rand()%4 == 1);
    }
    m->energy = get_physical_energy(m);
}

void update_grid(Molecules *m) {
    size_t i = rand() % m->size;
    double dE = get_deltaE(m, i);

    printf("%f\n", m->energy);
    // always accecpt downhill?
    if (dE <= 0.0) {
        m->grid[i] ^= true;
        m->energy += dE;
    } else {
        double u = (double)rand() / (double)RAND_MAX;
        double boltz = exp(-dE / m->Temperature);
        if (u < boltz) {
            m->grid[i] ^= true;
            m->energy += dE;
        }
    }
}

int get_deltaE(const Molecules *m, int i) {
    int x = i % m->w;
    int y = i / m->w;
    int num_n = 0;

    if (x > 0 && m->grid[i-1]) {
        num_n++;
    }
    
    if (x < m->w-1 && m->grid[i+1]) {
        num_n++;
    } 
    
    if (y > 0 && m->grid[i-m->w]) {
        num_n++;
    }
    if (y < m->h-1 && m->grid[i+m->w]) {
        num_n++;
    }

    if (m->grid[i]) {
        return +m->J * num_n + m->mu;
    } else {
        return -m->J * num_n - m->mu;
    }
}

// you dont need to keep track of seen! can just count only right and down!
size_t get_grid_energy(const Molecules *m) {
    size_t num_n = 0;

    for (int y = 0; y < m->h; y++) {
        for (int x = 0; x < m->w; x++) {
            int i = y * m->w + x;
            if (!m->grid[i]) continue;

            if (x < m->w - 1 && m->grid[i+1])
                num_n++;  

            if (y < m->h - 1 && m->grid[i+m->w])
                num_n++;  
        }
    }

    return num_n;  
}

double get_physical_energy(const Molecules *m) {
    size_t num_n = get_grid_energy(m);

    size_t occupied = 0;
    for (size_t i = 0; i < m->size; i++) {
        if (m->grid[i]) occupied++;
    }

    return -m->J * (double)num_n - m->mu * (double)occupied;
}