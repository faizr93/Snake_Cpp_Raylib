#include <raylib-cpp.hpp>
#include <algorithm>
#include "grid.h"
#include "utils.h"

float Grid::gridSize = 25.0f;
bool Grid::isScaling = false;

Grid::Grid()
{
    gridSize = 25.0f;
}

std::vector<int> Grid::getCommonScreenFactors()
{
    // Get screen dimensions
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Find common factors of width and height
    std::vector<int> factorsWidth = getFactors(screenWidth);
    std::vector<int> factorsHeight = getFactors(screenHeight);

    // Find common factors
    std::vector<int> commonFactors = getCommonFactors(screenWidth, screenHeight);

    return commonFactors;
}

void Grid::handleInput()
{
    isScaling = false;
    if (IsKeyPressed(KEY_KP_1))
    {
        ++gridSizesIterator;
        gridSize = gridSizes[gridSizesIterator % gridSizes.size()];
        isScaling = true;
    }
    else if (IsKeyPressed(KEY_KP_2))
    {
        --gridSizesIterator;
        gridSize = gridSizes[gridSizesIterator % gridSizes.size()];
        isScaling = true;
    }
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

void Grid::update()
{
}
void Grid::render() const
{
    for (int x = 0; x < GetScreenWidth(); x += Grid::gridSize)
        DrawLine(x, 0, x, GetScreenHeight(), DARKGRAY); // Vertical lines

    for (int y = 0; y < GetScreenHeight(); y += Grid::gridSize)
        DrawLine(0, y, GetScreenWidth(), y, DARKGRAY); // Horizontal lines
}