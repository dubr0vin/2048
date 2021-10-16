#include <iostream>
#include "src/game.h"
#include "src/ui/text_ui.h"

int main() {
    TextUI textUi;
    Game game(4, textUi);
    game.Play();
    return 0;
}
