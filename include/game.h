#pragma once
#include "snake.h"
#include "gameObject.h"
#include "grid.h"
#include "collisionHandler.h"

class Game : public GameObject
{
public:
    Grid grid;
    Snake snake;
    CollisionHandler collisionHandler;
    Game();
    void render() const;
    void update();
    void handleInput();
};