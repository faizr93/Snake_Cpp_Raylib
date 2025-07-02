#include "snakeSegment.h"
#include "grid.h"

// --- Construction ---

SnakeSegment::SnakeSegment(Grid& grid, Rectangle r, raylib::Color c)
    : gridRef(grid), rect(r), color(c)
{
    // If rect width/height are 0, set them to gridSize
    if (rect.width == 0 || rect.height == 0) {
        rect.width  = gridRef.gridSize;
        rect.height = gridRef.gridSize;
    }
}

// --- Rendering ---

void SnakeSegment::render() const {
    rect.Draw(color);
    rect.DrawLines(BLUE, rect.GetHeight() / 6);
}

// --- Update ---

void SnakeSegment::update() {
    // No-op for now
}
