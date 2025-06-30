#include "snake.h"
#include "grid.h"
#include "utils.h"

// --- Construction ---
Snake::Snake()
{
    init();
}

// --- Core game loop methods ---
void Snake::update()
{
    if (Grid::isScaling)
    {
        scale();
        Grid::isScaling = false;
        return;
    }

    static double lastMoveTime = 0;
    const double moveInterval = 0.15;
    double currentTime = GetTime();

    if (currentTime - lastMoveTime < moveInterval)
        return;

    for (auto &segment : segments)
        segment.update();

    lastMoveTime = currentTime;

    move();
    wrapPos();
}

void Snake::render() const
{
    for (auto &segment : segments)
        segment.render();
}

// --- Input and mechanics ---
void Snake::handleInput()
{
    // Directional input
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && snakeHeadDirection != DOWN)
        snakeHeadDirection = UP;
    else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && snakeHeadDirection != UP)
        snakeHeadDirection = DOWN;
    else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && snakeHeadDirection != RIGHT)
        snakeHeadDirection = LEFT;
    else if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && snakeHeadDirection != LEFT)
        snakeHeadDirection = RIGHT;
}

void Snake::move()
{
    if (segments.empty())
        return;

    // Store previous positions
    std::vector<raylib::Vector2> prevPositions;
    for (const auto &seg : segments)
        prevPositions.push_back(seg.rect.GetPosition());

    // Move head
    switch (snakeHeadDirection)
    {
    case UP:
        segments[0].rect.y -= Grid::gridSize;
        break;
    case DOWN:
        segments[0].rect.y += Grid::gridSize;
        break;
    case LEFT:
        segments[0].rect.x -= Grid::gridSize;
        break;
    case RIGHT:
        segments[0].rect.x += Grid::gridSize;
        break;
    }

    // Move body
    for (size_t i = 1; i < segments.size(); ++i)
        segments[i].rect.SetPosition(prevPositions[i - 1].x, prevPositions[i - 1].y);
}

void Snake::scale()
{
    static float lastGridSize = Grid::gridSize; // Keep track of previous grid size

    // Calculate scaling factor
    float scaleFactor = Grid::gridSize / lastGridSize;

    // Scale each segment's position proportionally
    for (auto& segment : segments)
    {
        segment.rect.x      *= scaleFactor;
        segment.rect.y      *= scaleFactor;
        segment.rect.width   = Grid::gridSize;
        segment.rect.height  = Grid::gridSize;
    }

    snapSnakeToGrid();

    lastGridSize = Grid::gridSize; // Update for next scale
}

void Snake::wrapPos()
{
    // Wrap horizontally
    if (segments[0].rect.GetX() < 0)
        segments[0].rect.SetX(GetScreenWidth() - Grid::gridSize);
    else if (segments[0].rect.x >= GetScreenWidth())
        segments[0].rect.SetX(0);

    // Wrap vertically
    if (segments[0].rect.GetY() < 0)
        segments[0].rect.SetY(GetScreenHeight() - Grid::gridSize);
    else if (segments[0].rect.y >= GetScreenHeight())
        segments[0].rect.SetY(0);
}

void Snake::snapSnakeToGrid()
{
    for (auto &segment : segments)
    {
        snapToGrid(segment.rect.x, Grid::gridSize);
        snapToGrid(segment.rect.y, Grid::gridSize);
    }
}

// --- Internal helpers ---
void Snake::init()
{
    segments.clear();
    for (size_t i = 0; i < length; ++i)
    {
        SnakeSegment segment;
        segment.rect.SetPosition(250, 250 + i * Grid::gridSize);
        segments.push_back(segment);
    }
    snapSnakeToGrid();
}

void Snake::grow()
{
    // TODO: Implement grow logic
}
bool Snake::isIntact() const
{
    for (size_t i = 1; i < segments.size(); ++i)
    {
        int dx = static_cast<int>(segments[i].rect.x - segments[i - 1].rect.x);
        int dy = static_cast<int>(segments[i].rect.y - segments[i - 1].rect.y);

        // Check for wrapping: if the absolute difference is larger than grid size, it's wrapping
        if (abs(dx) > Grid::gridSize || abs(dy) > Grid::gridSize)
            return false;

        // Segments must be adjacent: either dx or dy is exactly gridSize, the other is 0
        bool adjacent = (abs(dx) == Grid::gridSize && dy == 0) ||
                        (abs(dy) == Grid::gridSize && dx == 0);
        if (!adjacent)
            return false;

        // Also, both segments must be within screen bounds
        if (segments[i].rect.x     < 0 || segments[i].rect.x     >= GetScreenWidth()  ||
            segments[i].rect.y     < 0 || segments[i].rect.y     >= GetScreenHeight() ||
            segments[i - 1].rect.x < 0 || segments[i - 1].rect.x >= GetScreenWidth()  ||
            segments[i - 1].rect.y < 0 || segments[i - 1].rect.y >= GetScreenHeight())
            return false;
    }
    return true;
}
