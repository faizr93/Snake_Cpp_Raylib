#include "game.h"
#include <raylib-cpp.hpp>
#include "snake.h"

Game::Game()
{
}

void Game::handleInput()
{
    snake.handleInput();
    if(!snake.isIntact()) return; // Grid changee only if snake is intact
    grid.handleInput();
}

void Game::render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    grid.render();
    snake.render();
    EndDrawing();
    
}

void Game::update()
{
    grid.update();
    snake.update();
}