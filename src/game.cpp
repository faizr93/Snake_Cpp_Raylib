#include "game.h"

#include "snake.h"
#include "foodHandler.h"
#include "grid.h"

// --- Construction ---
Game::Game()
    : grid_(), snake_(grid_), foodHandler_(snake_, grid_)
{
}

// --- Input Handling ---
void Game::handleInput() {
    int keyPressed = GetKeyPressed();
    
    snake_.handleInput(keyPressed);
    if (!snake_.isIntact()) return; // Stop Grid Update if Snake is Wrapping #TODO Use Better Grid Change Logic so Snake Grid can be changed Even while Wrap
    grid_.handleInput(keyPressed);
    
}

// --- Rendering ---
void Game::render() const {
    BeginDrawing();
    ClearBackground(BLACK);
    grid_.render();
    snake_.render();
    foodHandler_.render();
    EndDrawing();
}

// --- Update ---

void Game::update() {
    grid_.update();
    snake_.update();
    foodHandler_.update();
}