#include <iostream>
#include "src/game.h"
#include "src/ui/text_ui.h"

int main(int argc, char **argv) {
    size_t field_size = 4;
    if (argc > 1) {
        field_size = atoi(argv[1]);
    }
    TextUI textUi;
    Game game(field_size, textUi);
    game.Play();
    return 0;
}
