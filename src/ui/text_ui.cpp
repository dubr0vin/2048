#include "text_ui.h"
#include <curses.h>
#include <chrono>
#include <thread>

void TextUI::DrawField(const Engine::Field &field, Engine::GameStatus status) {
    if (status == Engine::GameStatus::Lose) {
        endwin();
        std::printf("Game over!");
    } else {
        clear();
        size_t width = CalcWidth(field);

        bool first = true;
        for (const auto &x: field) {
            if (first) {
                addch(ACS_ULCORNER);
            } else {
                addch(ACS_LTEE);
            }
            for (size_t i = 0; i < x.size(); ++i) {
                for (size_t j = 0; j < width; ++j) {
                    addch(ACS_HLINE);
                }
                if (i == x.size() - 1) {
                    if (first) {
                        addch(ACS_URCORNER);
                    } else {
                        addch(ACS_RTEE);
                    }
                } else {
                    if (first) {
                        addch(ACS_TTEE);
                    } else {
                        addch(ACS_PLUS);
                    }
                }
            }
            printw("\n");
            first = false;

            for (const auto &y: x) {
                addch(ACS_VLINE);
                printw("%s", Nice(y, width).c_str());
            }
            addch(ACS_VLINE);
            printw("\n");
        }
        addch(ACS_LLCORNER);
        for (size_t i = 0; i < field[0].size(); ++i) {
            for (size_t j = 0; j < width; ++j) {
                addch(ACS_HLINE);
            }
            if (i == field[0].size() - 1) {
                addch(ACS_LRCORNER);
            } else {
                addch(ACS_BTEE);
            }
        }
        printw("\n:");
        refresh();
    }
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

size_t TextUI::CalcWidth(const Engine::Field &field) {
    size_t res = 0;
    for (const auto &x: field) {
        for (const auto &y: x) {
            res = std::max(res, std::to_string(y).size());
        }
    }
    return res;
}

std::string TextUI::Nice(int32_t x, size_t to) {

    std::string res = std::to_string(x);
    if (x == 0) {
        res = " ";
    }
    while (res.size() < to) {
        if (res.size() % 2 == 0) {
            res.push_back(' ');
        } else {
            res = " " + res;
        }
    }
    return res;
}

