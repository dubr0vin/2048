#include "text_ui.h"
#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <unistd.h>


void TextUI::DrawField(Engine::Field field, Engine::GameStatus status) {
    clear();
    for (const auto &x: field) {
        for (const auto &y: x) {
            printw("%d ", y);
        }
        printw("\n");
    }
    printw(":");
    refresh();
}


Engine::MoveDirection TextUI::ReadCommand() {
    while (true) {
        if (GetChar()) {
            int c = getch();
            printw("%d",c);
            refresh();
            if (c == 0x41) {
                return Engine::MoveDirection::Up;
            } else if (c == 0x42) {
                return Engine::MoveDirection::Down;
            } else if (c == 0x44) {
                return Engine::MoveDirection::Left;
            } else if (c == 0x43) {
                return Engine::MoveDirection::Right;
            }
        }
    }
}


TextUI::TextUI() {
    initscr();

    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
}

int TextUI::GetChar() {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

