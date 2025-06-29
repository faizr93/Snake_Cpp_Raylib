#pragma once
#include "snakeSegment.h"
#include "gameObject.h"

class Snake : public gameObject
{
public:
    Snake();
    std::vector<SnakeSegment> segments;
    gameObject::Direction snakeHeadDirection;
    void update() override;
    void render() override;
    void move();
    void clampSnakePosition();
    void handleInput();

private:
    void grow();
    void reset();
    int length = 7;
};