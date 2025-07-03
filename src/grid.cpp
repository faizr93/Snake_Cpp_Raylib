#include "grid.h"

#include <raylib-cpp.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

#include "utils.h"

// --- Construction ---

Grid::Grid(float gridSize)
: gridSize(25.0f), sizeChanged(false) {}

// --- Factor Utilities ---

std::vector<int> Grid::getCommonScreenFactors()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    std::vector<int> factorsWidth = getFactors(screenWidth);
    std::vector<int> factorsHeight = getFactors(screenHeight);

    std::vector<int> commonFactors = getCommonFactors(screenWidth, screenHeight);
    return commonFactors;
}

std::vector<int> Grid::getClampedFactors(const std::vector<int> &factors, int min, int max)
{
    std::vector<int> filtered;
    for (int factor : factors)
    {
        if (factor >= min && factor <= max)
            filtered.push_back(factor);
    }
    return filtered;
}

// --- Input Handling ---

void Grid::handleInput(int keyPressed)
{
    sizeChanged = false;
    if (keyPressed == KEY_KP_1)
    {
        ++gridSizesIterator;
        gridSize = gridSizes[gridSizesIterator % gridSizes.size()];
        sizeChanged = true;
    }
    else if (keyPressed == KEY_KP_2)
    {
        --gridSizesIterator;
        gridSize = gridSizes[gridSizesIterator % gridSizes.size()];
        sizeChanged = true;
    }
}

// --- Update & Render ---

void Grid::update() {}

void Grid::render() const
{
    for (int x = 0; x < GetScreenWidth(); x += Grid::gridSize)
        DrawLine(x, 0, x, GetScreenHeight(), DARKGRAY);

    for (int y = 0; y < GetScreenHeight(); y += Grid::gridSize)
        DrawLine(0, y, GetScreenWidth(), y, DARKGRAY);
}

void Grid::printGridSize() const
{
    std::cout<<gridSize<<std::endl;
}
