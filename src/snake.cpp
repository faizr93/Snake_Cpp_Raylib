#include "snake.h"
#include "grid.h"
#include "utils.h"
#include "foods.h"

// --- Construction ---

Snake::Snake(Grid& grid, std::string name, int length, raylib::Color snakeColor)
    : playerName(name), gridRef(grid)
{
    lastMoveTime = 0.0;
    segments.clear();
    for (size_t i = 0; i < length; ++i)
    {
        SnakeSegment segment(grid, {250, 250 + i * gridRef.gridSize}, snakeColor);
        segments.push_back(segment);
    }
    snapSnakeToGrid();
}

// --- Core game loop methods ---

void Snake::update()
{
    moved = false;
    if (gridRef.isScaling)
    {
        scale();
        gridRef.isScaling = false;
        return;
    }

    // Use Raylib's GetFrameTime for delta time
    static double moveAccumulator = 0.0;
    double deltaTime = GetFrameTime();
    moveAccumulator += deltaTime;

    for (auto &segment : segments)
        segment.update();

    // Move the snake based on accumulated time
    if (moveAccumulator >= moveInterval)
    {
        move();
        moved = true;
        wrapPos();
        moveAccumulator -= moveInterval; // preserve leftover time
    }
}

void Snake::render() const
{
    for (const auto &segment : segments)
        segment.render();
}

// --- Input and mechanics ---

const std::vector<raylib::Vector2> Snake::getSnakePos()
{
    std::vector<raylib::Vector2> positions;
    for (const auto &seg : segments)
        positions.push_back(seg.rect.GetPosition());
    return positions;
}

void Snake::handleInput()
{
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

    std::vector<raylib::Vector2> prevPositions = getSnakePos();

    switch (snakeHeadDirection)
    {
    case UP:
        segments[0].rect.y -= gridRef.gridSize;
        break;
    case DOWN:
        segments[0].rect.y += gridRef.gridSize;
        break;
    case LEFT:
        segments[0].rect.x -= gridRef.gridSize;
        break;
    case RIGHT:
        segments[0].rect.x += gridRef.gridSize;
        break;
    }

    for (size_t i = 1; i < segments.size(); ++i)
        segments[i].rect.SetPosition(prevPositions[i - 1].x, prevPositions[i - 1].y);
}

void Snake::scale()
{
    static float lastGridSize = gridRef.gridSize;
    float scaleFactor = gridRef.gridSize / lastGridSize;

    for (auto &segment : segments)
    {
        segment.rect.SetPosition(segment.rect.x * scaleFactor, segment.rect.y * scaleFactor);
        segment.rect.SetSize(gridRef.gridSize, gridRef.gridSize);
    }

    snapSnakeToGrid();
    lastGridSize = gridRef.gridSize;
}

void Snake::wrapPos()
{
    Vector2 headPos = getHeadPos();

    if (headPos.x < 0)
        setHeadPos({GetScreenWidth() - gridRef.gridSize, headPos.y});
    else if (headPos.x >= GetScreenWidth())
        setHeadPos({0, headPos.y});

    if (headPos.y < 0)
        setHeadPos({headPos.x, GetScreenHeight() - gridRef.gridSize});
    else if (headPos.y >= GetScreenHeight())
        setHeadPos({headPos.x, 0});
}

void Snake::snapSnakeToGrid()
{
    for (auto &segment : segments)
    {
        snapToGrid(segment.rect.x, gridRef.gridSize);
        snapToGrid(segment.rect.y, gridRef.gridSize);
    }
}

bool Snake::isIntact() const
{
    for (size_t i = 1; i < segments.size(); ++i)
    {
        int dx = static_cast<int>(segments[i].rect.x - segments[i - 1].rect.x);
        int dy = static_cast<int>(segments[i].rect.y - segments[i - 1].rect.y);

        if (abs(dx) > gridRef.gridSize || abs(dy) > gridRef.gridSize)
            return false;

        bool adjacent = (abs(dx) == gridRef.gridSize && dy == 0) ||
                        (abs(dy) == gridRef.gridSize && dx == 0);
        if (!adjacent)
            return false;

        if (segments[i].rect.x < 0 || segments[i].rect.x >= GetScreenWidth() ||
            segments[i].rect.y < 0 || segments[i].rect.y >= GetScreenHeight() ||
            segments[i - 1].rect.x < 0 || segments[i - 1].rect.x >= GetScreenWidth() ||
            segments[i - 1].rect.y < 0 || segments[i - 1].rect.y >= GetScreenHeight())
            return false;
    }
    return true;
}

// --- Getters/Setters ---

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
