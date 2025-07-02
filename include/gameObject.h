#ifndef SNAKE_CPP_RAYLIB_GAMEOBJECT_H_
#define SNAKE_CPP_RAYLIB_GAMEOBJECT_H_

class GameObject
{
public:
    virtual void update() = 0;
    virtual void render() const = 0;
};

#endif // SNAKE_CPP_RAYLIB_GAMEOBJECT_H_