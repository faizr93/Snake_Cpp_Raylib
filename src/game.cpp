#include "game.h"
#include "snake.h"

// --- Construction ---

Game::Game() {}

// --- Input Handling ---

void Game::handleInput() {
    snake_.handleInput();
    if (!snake_.isIntact()) return;
    grid_.handleInput();
}

// --- Rendering ---

void Game::render() const {
    BeginDrawing();
    ClearBackground(BLACK);
    grid_.render();
    snake_.render();
    EndDrawing();
}

// --- Update ---

void Game::update() {
    grid_.update();
    snake_.update();
}