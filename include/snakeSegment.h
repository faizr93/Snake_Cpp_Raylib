#ifndef SNAKE_CPP_RAYLIB_SNAKESEGMENT_H_
#define SNAKE_CPP_RAYLIB_SNAKESEGMENT_H_

#include <raylib-cpp.hpp>

#include "gameObject.h"
#include "grid.h"

class SnakeSegment : public GameObject
{
public:
    int gridX = 0;
    int gridY = 0;
    raylib::Rectangle rect;
    raylib::Color color;

    SnakeSegment(
        int gridX = 0,
        int gridY = 0,
        float gridSize = 0.0f,
        raylib::Color color = GREEN)
        : gridX(gridX), gridY(gridY), rect(gridX * gridSize, gridY * gridSize, gridSize, gridSize), color(color)
    {
    }

    void syncRect(float gridSize) {
        rect.SetPosition(gridX * gridSize, gridY * gridSize);
        rect.SetSize(gridSize, gridSize);
    }

    // --- Rendering ---
    void render() const override
    {
        rect.Draw(color);
        rect.DrawLines(BLUE, rect.GetHeight() / 6);
    }
};

#endif // SNAKE_CPP_RAYLIB_SNAKESEGMENT_H_