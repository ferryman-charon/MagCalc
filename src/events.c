#include "events.h"

void game_init_pixels(struct Game *g) {
    for (size_t i = 0; i < WINDOW_HEIGHT*WINDOW_WIDTH; i++) {
        uint32_t color_val;
        if (rand()%4 == 1) {
            color_val = 0xffffffff;
        } else {
            color_val = 0xff0000ff;
        }
        g->pixels[i] = color_val;
    }
}

void game_update_pixels(struct Game *g) {
    size_t max_size = WINDOW_WIDTH*WINDOW_HEIGHT;
    int i1 = rand()%max_size;
    int i2 = rand()%max_size;

    if (g->pixels[i1] != g->pixels[i2]) {
        uint32_t temp = g->pixels[i1];
        g->pixels[i1] = g->pixels[i2];
        g->pixels[i2] = temp;
    }

    for (size_t i = 0; i < WINDOW_HEIGHT*WINDOW_WIDTH; i++) {
        uint32_t color_val;
        if (rand()%4 == 1) {
            color_val = 0xffffffff;
        } else {
            color_val = 0xff0000ff;
        }
        g->pixels[i] = color_val;
    }
}


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
                        game_init_pixels(g);
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