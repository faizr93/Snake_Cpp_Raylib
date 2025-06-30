#pragma once
#include "snake.h"
#include "gameObject.h"
#include "grid.h"

class Game : public GameObject
{
public:
    Grid grid;
    Snake snake;
    Game();
    void render() const;
    void update();
    void handleInput();
    
};