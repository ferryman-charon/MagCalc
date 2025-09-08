#include "game.h"
#include "events.h"

void game_render_colors(struct Game *g);
void game_events(struct Game *g);
bool game_draw(struct Game *g);

bool game_init_sdl(struct Game *g) {
    if (!SDL_Init(SDL_FLAGS)) {
        fprintf(stderr, "Error initializing SDL3: %s\n", SDL_GetError());
        return false;
    }

    g->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!g->window) {
        fprintf(stderr, "Error creating Window: %s\n", SDL_GetError());
        return false;
    }

    g->renderer = SDL_CreateRenderer(g->window, NULL);
    if (!g->renderer) {
        fprintf(stderr, "Error creating Renderer: %s\n", SDL_GetError());
        return false;
    }

    SDL_Surface *icon_surf = IMG_Load("images/logo.png");
    if (!icon_surf) {
        fprintf(stderr, "Error loading Surface: %s",SDL_GetError());
        return false;
    }
    if (!SDL_SetWindowIcon(g->window, icon_surf)) {
        fprintf(stderr, "Error setting icon: %s",SDL_GetError());
        SDL_DestroySurface((icon_surf));
        return false;
    }
    SDL_DestroySurface(icon_surf);

    srand(time(NULL));
    
    return true;
}

bool game_new(struct Game **game) {
    *game = calloc(1, sizeof(struct Game));

    if (*game == NULL) {
        fprintf(stderr, "Failed Creating game!\n");
        return false;
    }
    struct Game *g = *game;
    
    if (!game_init_sdl(g)) {
        return false;
    }
    
    g->pixels = calloc(WINDOW_HEIGHT*WINDOW_WIDTH, sizeof(uint32_t));
    if (!g->pixels) {
        free(g);
        *game = NULL;
        fprintf(stderr, "Error creating Renderer: %s\n", SDL_GetError());
        return false;
    }
    
    g->out_screen = SDL_CreateTexture(g->renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
        WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!g->out_screen) {
        fprintf(stderr, "Failed Creating texture!: %s\n", SDL_GetError());
        return false;
    }

    g->is_running = true;
    return true;
}

void game_free(struct Game **game) {
    if (*game) {
        struct Game *g = *game;

        if (g->out_screen) {
            SDL_DestroyTexture(g->out_screen);
            g->out_screen = NULL;
        }

        if (g->pixels) {
            free(g->pixels);
            g->pixels = NULL;
        }
        
        if (g->renderer) {
            SDL_DestroyRenderer(g->renderer);
            g->renderer = NULL;
        }

        if (g->window) {
            SDL_DestroyWindow(g->window);
            g->window = NULL;
        }

        SDL_Quit();
        free(g);
        *game = NULL;
        printf("All good!\n");
    }
}

bool game_draw(struct Game *g) {

    if (!SDL_RenderClear(g->renderer)) {
        fprintf(stderr, "Error clearing renderer: %s\n", SDL_GetError());
        return 0;
    }
    game_update_pixels(g);
    if (!SDL_UpdateTexture(g->out_screen, NULL, g->pixels, PITCH)) {
        fprintf(stderr, "Error updating texture: %s\n", SDL_GetError());
        return 0;
    }   

    if (!SDL_RenderTexture(g->renderer, g->out_screen, NULL, NULL)) {
        fprintf(stderr, "Error rendering texture: %s\n", SDL_GetError());
        return 0;
    }

    if (!SDL_RenderPresent(g->renderer)) {
        fprintf(stderr, "Error presenting renderer: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}

void game_run(struct Game *g) {

    game_update_pixels(g);
    while (g->is_running) {
        game_events(g);        
        
        if (!game_draw(g)) {
            g->is_running = false;
        }
        SDL_Delay(16);
    }
}