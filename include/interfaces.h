#pragma once

class Snake;

class ICollideable
{
public:
    virtual void handleCollision(Snake& snake) = 0;
};