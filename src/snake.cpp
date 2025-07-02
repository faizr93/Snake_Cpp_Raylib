#include "snake.h"
#include "grid.h"
#include "utils.h"
#include "foods.h"

// --- Construction ---

Snake::Snake(std::string name, int length, raylib::Color snakeColor)
{
    segments.clear();
    playerName = name;

    for (size_t i = 0; i < length; ++i)
    {
        // segment.color = snakeColor;
        // segment.rect.SetPosition(250, 250 + i * Grid::gridSize);
        SnakeSegment segment({250, 250 + i * Grid::gridSize}, snakeColor);
        segments.push_back(segment);
    }
    snapSnakeToGrid();
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
const std::vector<raylib::Vector2> Snake::getSnakePos()
{
    std::vector<raylib::Vector2> positions;
    for (const auto &seg : segments)
    {
        positions.push_back(seg.rect.GetPosition());
    }
    return positions;
}
void Snake::move()
{
    if (segments.empty())
        return;

    // Store previous positions
    std::vector<raylib::Vector2> prevPositions = getSnakePos();

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
    for (auto &segment : segments)
    {
        segment.rect.SetPosition(segment.rect.x * scaleFactor, segment.rect.y * scaleFactor);
        segment.rect.SetSize(Grid::gridSize, Grid::gridSize);
    }

    snapSnakeToGrid();

    lastGridSize = Grid::gridSize; // Update for next scale
}

void Snake::wrapPos()
{
    Vector2 headPos = getHeadPos();
    // Wrap horizontally
    if (headPos.x < 0)
        setHeadPos({GetScreenWidth() - Grid::gridSize, headPos.y});
    else if (headPos.x >= GetScreenWidth())
        setHeadPos({0,headPos.y});

    // Wrap vertically
    if (headPos.y < 0)
        setHeadPos({headPos.x,GetScreenHeight() - Grid::gridSize});
    else if (headPos.y >= GetScreenHeight())
        setHeadPos({headPos.x,0});
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

const raylib::Vector2 Snake::getHeadPos()
{
    return segments[0].rect.GetPosition();
}
void Snake::setHeadPos(Vector2 newPos) 
{
    segments[0].rect.SetX(newPos.x);
    segments[0].rect.SetY(newPos.y);
}

void Snake::grow()
{
    segments.push_back(SnakeSegment());
    length++;
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
        if (segments[i].rect.x < 0 || segments[i].rect.x >= GetScreenWidth() ||
            segments[i].rect.y < 0 || segments[i].rect.y >= GetScreenHeight() ||
            segments[i - 1].rect.x < 0 || segments[i - 1].rect.x >= GetScreenWidth() ||
            segments[i - 1].rect.y < 0 || segments[i - 1].rect.y >= GetScreenHeight())
            return false;
    }
    return true;
}
