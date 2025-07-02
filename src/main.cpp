#include "game.h"
#include <raylib-cpp.hpp>
#include "grid.h" // For debug
#include <iostream>

// --- Main Entry Point ---

int main() {
    raylib::Window window(800, 600, "Cobra", FLAG_VSYNC_HINT);
    Game Cobra;

    while (!WindowShouldClose()) {
        Cobra.handleInput();
        Cobra.update();
        Cobra.render();
        std::cout << Grid::gridSize;
    }

    return 0;
}