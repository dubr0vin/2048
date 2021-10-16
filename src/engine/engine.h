#pragma once

#include <random>
#include <vector>

class Engine {
public:
    using Field = std::vector<std::vector<int32_t>>;
    enum class MoveDirection {
        Left, Right, Down, Up
    };

    enum class GameStatus{
        Running,
        Lose,
        //Win You can't win in 2048 game!
    };

    Engine(size_t field_size);

    void Turn(Engine::MoveDirection md);

    GameStatus GetStatus();

    Field GetRawField();

    void Start();
private:
    Field data_;

    void AddCell();

    bool Lose();

    void Move(MoveDirection mv);

    std::vector<std::pair<size_t, size_t >> FindEmptyCells();

    void MoveRight(std::vector<int32_t> &vec);

    void Transposition();

    void Reverse();
};

