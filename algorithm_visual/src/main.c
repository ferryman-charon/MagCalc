#include "main.h"
#include "game.h"

int main(void) {
    bool exit_status = EXIT_FAILURE;
    if (CELL_SIZE < 1 || CELL_SIZE > WINDOW_WIDTH || CELL_SIZE > WINDOW_HEIGHT) {
        return exit_status;
    }

    struct Game *game = NULL;

    if (game_new(&game)) {
        game_run(game);

        exit_status = EXIT_SUCCESS;
    }

    game_free(&game);

    return exit_status;
}