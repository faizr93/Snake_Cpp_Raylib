#pragma once
#include "gameObject.h"

class Grid: public gameObject
{
public: 
    static bool isScaling;
    static float gridSize;

    Grid();

    std::vector<int> getCommonScreenFactors();
    std::vector<int> getClampedFactors(const std::vector<int>& factors, int min, int max);

    std::vector<int> gridSizes         = getClampedFactors(getCommonScreenFactors(), 10, 50);
    int              gridSizesIterator = gridSizes.size() / 2;  // Start in the middle of the grid sizes

    void handleInput();
    void update() override;
    void render() override;
};