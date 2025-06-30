#pragma once
#include "gameObject.h"
#include <raylib-cpp.hpp>

class food : public GameObject {
public:
    raylib::Rectangle rect;
    int maxFoodCount;

    raylib::Vector2 getRandomPos(const std::vector<raylib::Vector2>& snakePos, float lowerBound, float upperBound);
    raylib::Vector2 generateFood(const std::vector<raylib::Vector2>& snakePositions, float min, float max);
    void render() const override ;
    void update() override;
    void snapToGrid();
};
