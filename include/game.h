#ifndef SNAKE_CPP_RAYLIB_GAME_H_
#define SNAKE_CPP_RAYLIB_GAME_H_

#include "snake.h"
#include "gameObject.h"
#include "grid.h"

/// Main game controller: owns grid, snake, and collisions.
class Game
{
public:
    Game();              // Init core game state
    void handleInput();  // Process input
    void update();       // Progress game state
    void render() const; // Draw game

private:
    Grid grid_;                         // Game board
    Snake snake_;                       // Player snake
};

#endif // SNAKE_CPP_RAYLIB_GAME_H_
