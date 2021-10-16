#pragma once

#include "ui.h"

class TextUI: public UI{
public:
    TextUI();
    void DrawField(const Engine::Field& field, Engine::GameStatus status) override;
    Engine::MoveDirection ReadCommand() override;

private:
    int GetChar();
    size_t CalcWidth(const Engine::Field& field);
    std::string Nice(int32_t x, size_t to);
};


