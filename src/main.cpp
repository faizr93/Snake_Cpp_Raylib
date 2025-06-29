#include "game.h"
#include "raylib-cpp.hpp"
#include "grid.h" //FOR DEBUG
#include <iostream>

int main()
{
    raylib::Window window(800, 600, "Snake", FLAG_VSYNC_HINT);
    Game Snake;

    while (!WindowShouldClose())
    {
        Snake.handleInput();
        Snake.update();
        Snake.render();
        std::cout<<Grid::gridSize;
    }

    return 0;
}