#pragma once

#include <raylib-cpp.hpp>
#include "gameObject.h"
#include "grid.h"

class SnakeSegment : public GameObject
{
public:
    raylib::Rectangle rect;
    raylib::Color color;
    Grid& gridRef;

    SnakeSegment(Grid& gridRef = *(Grid*)nullptr,
        Rectangle rect = {250, 250, 0, 0}, // Use a constant or 0 here
        raylib::Color color = GREEN
    );

    void render() const override;
    void update() override;
};