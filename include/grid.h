#pragma once
#include "gameObject.h"

class Grid : public gameObject
{
public:
    static bool isScaling;
    static float gridSize;
    Grid();
    void update() override;
    void render() override;
};