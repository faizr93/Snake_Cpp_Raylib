#include "game.h"
#include "snake.h"

// --- Construction ---

Game::Game() {}

// --- Input Handling ---

void Game::handleInput() {
    snake.handleInput();
    if (!snake.isIntact()) return;
    grid.handleInput();
}

// --- Rendering ---

void Game::render() const {
    BeginDrawing();
    ClearBackground(BLACK);
    grid.render();
    snake.render();
    EndDrawing();
}

// --- Update ---

void Game::update() {
    grid.update();
    snake.update();
}