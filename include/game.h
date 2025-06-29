#pragma once
#include "snake.h"
#include "gameObject.h"
#include "grid.h"

class Game : public gameObject
{
public:
    Grid grid;
    Snake snake;
    Game();
    void render();
    void update();
    void handleInput();
    
};