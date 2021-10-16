#pragma once

#include "../engine/engine.h"

class UI {
public:
    virtual void DrawField(Engine::Field field, Engine::GameStatus status) = 0;

    virtual Engine::MoveDirection ReadCommand() = 0;
};