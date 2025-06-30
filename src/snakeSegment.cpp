#include "snakeSegment.h"
#include "grid.h"

SnakeSegment::SnakeSegment()
    : rect(250, 250, Grid::gridSize, Grid::gridSize), color(GREEN) {}

void SnakeSegment::render() const
{
    rect.Draw(color);
    rect.DrawLines(BLUE, rect.GetHeight()/6);
}

void SnakeSegment::update()
{
    // No-op for now
}
