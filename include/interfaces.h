#pragma once

class Snake;

class ICollideable
{
public:
    virtual void onCollision(Snake &snake) = 0;
};