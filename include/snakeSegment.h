#pragma once
#include <raylib-cpp.hpp>
#include "gameObject.h"

class SnakeSegment : public gameObject {
public:
    raylib::Rectangle rect;
    raylib::Color color;
    SnakeSegment();
    void render() override;
    void update() override;
};


