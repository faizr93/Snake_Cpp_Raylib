#include "game.h"
#include <raylib-cpp.hpp>
#include "snake.h"

Game::Game()
{
}

void Game::handleInput()
{
    snake.handleInput();
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
    snake.update();
}