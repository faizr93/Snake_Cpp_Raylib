#pragma once

class GameObject
{
public:
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    virtual void update() = 0;
    virtual void render() const = 0;
};