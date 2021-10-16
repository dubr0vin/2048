#pragma once

#include "engine/engine.h"
#include "ui/ui.h"

class Game {
public:
    Game(size_t field_size, UI& ui);

    void Play();

private:
    Engine engine_;
    UI& ui_;
};

