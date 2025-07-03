#include "game.h"

#include <iostream>
#include <raylib-cpp.hpp>

#include "grid.h"


// --- Main Entry Point ---

int main() {
  raylib::Window window(800, 600, "Cobra", FLAG_VSYNC_HINT);
  Game Cobra;

  while (!WindowShouldClose()) {
    Cobra.handleInput();
    Cobra.update();
    Cobra.render();

  }

  return 0;
}