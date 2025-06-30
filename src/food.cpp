#include "food.h"
#include <algorithm>
#include <raylib-cpp.hpp>

raylib::Vector2 food::getRandomPos(const std::vector<raylib::Vector2>& snakePositions, float min, float max)
{
    raylib::Vector2 randomPos;
    snapToGrid();

    do {
        randomPos.x = (float)GetRandomValue(0, GetScreenWidth());
        randomPos.y = (float)GetRandomValue(0, GetScreenHeight());
    } while (std::find(snakePositions.begin(), snakePositions.end(), randomPos) != snakePositions.end());

    return randomPos;
}

raylib::Vector2 food::generateFood(const std::vector<raylib::Vector2>& snakePositions, float min, float max)
{
    return raylib::Vector2();
}

void food::snapToGrid()
{
    // Implement grid snapping for food here if needed
}

void food::render() const
{
    rect.Draw(RED);
}

void food::update()
{
    if (maxFoodCount)
    {
        /* code */
    }
}
