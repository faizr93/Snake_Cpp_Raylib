#pragma once
#include <raylib-cpp.hpp>
#include "gameObject.h"

class SnakeSegment : public GameObject {
public:
    raylib::Rectangle rect;
    raylib::Color color;
    SnakeSegment();
    void render() const override;
    void update() override;
};


