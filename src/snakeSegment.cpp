#include "snakeSegment.h"
#include "grid.h"

SnakeSegment::SnakeSegment(Rectangle r, raylib::Color c)
    : rect(r), color(c) {}

void SnakeSegment::render() const
{
    rect.Draw(color);
    rect.DrawLines(BLUE, rect.GetHeight() / 6);
}

void SnakeSegment::update()
{
    // No-op for now
}
