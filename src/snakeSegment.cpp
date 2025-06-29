#include "snakeSegment.h"
#include "grid.h"

SnakeSegment::SnakeSegment()
    : rect(250, 250, Grid::gridSize, Grid::gridSize), color(GREEN) {}

void SnakeSegment::render()
{
    DrawRectangleRec(rect, color);
    DrawRectangleLinesEx(rect, 3, RED);
}

void SnakeSegment::update()
{
    // No-op for now
}
