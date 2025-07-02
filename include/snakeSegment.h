#pragma once
#include <raylib-cpp.hpp>
#include "gameObject.h"

class SnakeSegment : public GameObject
{
public:
    raylib::Rectangle rect;
    raylib::Color color;

    SnakeSegment(
        Rectangle rect = {250, 250, Grid::gridSize, Grid::gridSize},
        raylib::Color color = GREEN);
    void render() const override;
    void update() override;
};