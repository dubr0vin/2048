#pragma once

#include "ui.h"

class TextUI: public UI{
public:
    TextUI();
    void DrawField(Engine::Field field, Engine::GameStatus status) override;
    Engine::MoveDirection ReadCommand() override;

private:
    int GetChar();
};


