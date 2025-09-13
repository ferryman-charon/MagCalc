#include "events.h"
#include "draw_molecules.h"

void game_events(struct Game *g) {
    while (SDL_PollEvent(&g->event)) {
        switch (g->event.type) {
            case SDL_EVENT_QUIT:
                g->is_running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                switch (g->event.key.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        g->is_running = false;
                        break;
                    case SDL_SCANCODE_SPACE:
                        update_grid(g->molecule_grid);
                        break;
                    case SDL_SCANCODE_R:
                        grid_reset_values(g->molecule_grid);
                        break;
                    default:
                        break;
                }
                break;
            
            case SDL_EVENT_MOUSE_WHEEL:
                break;
            default: 
                break;
            }
    }
}