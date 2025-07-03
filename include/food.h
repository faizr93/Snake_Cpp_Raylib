#ifndef SNAKE_CPP_RAYLIB_FOODS_H_
#define SNAKE_CPP_RAYLIB_FOODS_H_

#include <raylib-cpp.hpp>

#include "gameObject.h"

// Basic Food Class
struct Food : public GameObject
{
    int gridX = 0;
    int gridY = 0;
    int scoreValue;
    bool isEaten = false;
    raylib::Color color;
    raylib::Rectangle rect;

    Food(int gridX = 0, int gridY = 0, float gridSize = 0.0f, raylib::Color color = RED, int scoreValue = 1)
        : gridX(gridX), gridY(gridY), rect(gridX * gridSize, gridY * gridSize, gridSize, gridSize), color(color), scoreValue(scoreValue) {}

    void syncRect(float gridSize) {
        rect.SetPosition(gridX * gridSize, gridY * gridSize);
        rect.SetSize(gridSize, gridSize);
    }

    void render() const { rect.Draw(color); }
};

#endif // SNAKE_CPP_RAYLIB_FOODS_H_