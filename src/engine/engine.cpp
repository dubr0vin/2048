#include "engine.h"

Engine::Engine(size_t field_size) {
    data_.resize(field_size, std::vector<int32_t>(field_size, 0));
}

void Engine::AddCell() {
    auto empty_cells = FindEmptyCells();
    std::shuffle(empty_cells.begin(), empty_cells.end(), std::mt19937(std::random_device()()));
    data_[empty_cells.front().first][empty_cells.front().second] = 1;
}

bool Engine::Lose() {
    auto empty_cells = FindEmptyCells();
    return empty_cells.empty();
}

void Engine::Move(MoveDirection mv) {
    if (mv == MoveDirection::Up || mv == MoveDirection::Down) {
        Transposition();
    }
    if (mv == MoveDirection::Right || mv == MoveDirection::Down) {
        Reverse();
    }
    for (auto &x: data_) {
        MoveRight(x);
    }
    if (mv == MoveDirection::Right || mv == MoveDirection::Down) {
        Reverse();
    }
    if (mv == MoveDirection::Up || mv == MoveDirection::Down) {
        Transposition();
    }
}

std::vector<std::pair<size_t, size_t>> Engine::FindEmptyCells() {
    std::vector<std::pair<size_t, size_t>> empty_cells;
    for (size_t i = 0; i < data_.size(); ++i) {
        for (size_t j = 0; j < data_.size(); ++j) {
            if (data_[i][j] == 0) {
                empty_cells.emplace_back(i, j);
            }
        }
    }
    return empty_cells;
}

void Engine::MoveRight(std::vector<int32_t> &vec) {
    std::vector<int32_t> res;
    int32_t last = 0;
    for (auto x: vec) {
        if (x == 0) {
            continue;
        }
        if (last == x) {
            res.push_back(x * 2);
            last = 0;
        } else {
            if (last != 0) {
                res.push_back(last);
            }
            last = x;
        }
    }
    if (last != 0) {
        res.push_back(last);
    }
    res.resize(vec.size(), 0);
    vec.swap(res);
}

void Engine::Transposition() {
    for (int i = 0; i < data_.size(); ++i) {
        for (int j = i; j < data_[i].size(); ++j) {
            std::swap(data_[i][j], data_[j][i]);
        }
    }
}

void Engine::Reverse() {
    for (auto &x: data_) {
        std::reverse(x.begin(), x.end());
    }
}

Engine::Field Engine::GetRawField() {
    return data_;
}

void Engine::Turn(Engine::MoveDirection md) {
    Move(md);
    if (!Lose()) {
        AddCell();
    }
}

Engine::GameStatus Engine::GetStatus() {
    if (Lose()) {
        return GameStatus::Lose;
    }
    return GameStatus::Running;
}

void Engine::Start() {
    AddCell();

}
