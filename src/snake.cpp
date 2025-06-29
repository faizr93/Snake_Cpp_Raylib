#include "snake.h"
#include "grid.h"
Snake::Snake()
{
    reset();
}

void Snake::handleInput()
{
    Grid::isScaling = false;
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && snakeHeadDirection != DOWN)
        snakeHeadDirection = UP;
    else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && snakeHeadDirection != UP)
        snakeHeadDirection = DOWN;
    else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && snakeHeadDirection != RIGHT)
        snakeHeadDirection = LEFT;
    else if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && snakeHeadDirection != LEFT)
        snakeHeadDirection = RIGHT;
    else if (IsKeyPressed(KEY_KP_1)){
        Grid::gridSize += 5;
        Grid::isScaling = true;}
    else if (IsKeyPressed(KEY_KP_2)){
        Grid::gridSize -= 5;
        Grid::isScaling = true;}
        Grid::clampGridSize();
}

void Snake::grow() { /* ... */ }

void Snake::reset()
{
    segments.clear();
    snakeHeadDirection = gameObject::UP;

    for (size_t i = 0; i < length; i++)
    {
        SnakeSegment segment;
        segment.rect.SetPosition(250, 250 + i * Grid::gridSize);
        segments.push_back(segment);
    }
}

void Snake::update()
{
    if (Grid::isScaling)
    {
        reset();
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
    clampSnakePosition();
}

void Snake::render()
{
    for (auto &segment : segments)
        segment.render();
}

void Snake::move()
{
    if (segments.empty())
        return;

    std::vector<raylib::Vector2> prevPositions;
    for (const auto &seg : segments)
        prevPositions.push_back(seg.rect.GetPosition());

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

    for (size_t i = 1; i < segments.size(); ++i)
        segments[i].rect.SetPosition(prevPositions[i - 1].x, prevPositions[i - 1].y);
}

void Snake::clampSnakePosition()
{
    // Normal wrapping logic
    if (segments[0].rect.GetX() < 0)
        segments[0].rect.SetX(GetScreenWidth() - Grid::gridSize);
    else if (segments[0].rect.x >= GetScreenWidth())
        segments[0].rect.SetX(0);

    if (segments[0].rect.GetY() < 0)
        segments[0].rect.SetY(GetScreenHeight() - Grid::gridSize);
    else if (segments[0].rect.y >= GetScreenHeight())
        segments[0].rect.SetY(0);
}