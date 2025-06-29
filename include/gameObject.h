#pragma once

class gameObject
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
    virtual void render() = 0;
};