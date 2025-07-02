#ifndef SNAKE_CPP_RAYLIB_INTERFACES_H_
#define SNAKE_CPP_RAYLIB_INTERFACES_H_

class Snake;

class ICollideable
{
public:
    virtual void handleCollision(Snake& snake) = 0;
};

#endif // SNAKE_CPP_RAYLIB_INTERFACES_H_