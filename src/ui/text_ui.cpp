#include "text_ui.h"
#include <curses.h>
#include <chrono>
#include <thread>

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
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
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

