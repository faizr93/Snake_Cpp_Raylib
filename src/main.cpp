#include "game.h"
#include "raylib-cpp.hpp"

int main()
{
    raylib::Window window(800, 600, "Snake", FLAG_VSYNC_HINT);
    Game Snake;

    while (!WindowShouldClose())
    {
        Snake.handleInput();
        Snake.update();
        Snake.render();
    }

    return 0;
}