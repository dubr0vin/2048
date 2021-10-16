#include "game.h"


Game::Game(size_t field_size, UI &ui) : engine_(field_size), ui_(ui) {

}

void Game::Play() {
    engine_.Start();
    while (engine_.GetStatus() == Engine::GameStatus::Running) {
        ui_.DrawField(engine_.GetRawField(), engine_.GetStatus());
        engine_.Turn(ui_.ReadCommand());
    }
    ui_.DrawField(engine_.GetRawField(), engine_.GetStatus());
}
