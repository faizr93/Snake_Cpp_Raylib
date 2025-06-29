#include <raylib-cpp.hpp>
#include "grid.h"

float Grid::gridSize = 25.0f;
bool Grid::isScaling = false;

Grid::Grid()
{
    gridSize = 25.0f;
}
void Grid::update()
{
    if (isScaling)
    {
        /* code */
    }
    
}
void Grid::render()
{
    for (int x = 0; x < GetScreenWidth(); x += Grid::gridSize)
    {
        DrawLine(x, 0, x, GetScreenHeight(), DARKGRAY);
    }
    for (int y = 0; y < GetScreenHeight(); y += Grid::gridSize)
    {
        DrawLine(0, y, GetScreenWidth(), y, DARKGRAY);
    }
}