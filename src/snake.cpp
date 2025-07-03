#include "snake.h"

#include <vector>
#include <string>
#include <raylib-cpp.hpp>

#include "grid.h"
#include "utils.h"
#include "food.h"
#include "snakeSegment.h"
#include <iostream>

// --- Construction ---

Snake::Snake(Grid &grid, std::string name, int length, raylib::Color snakeColor)
    : playerName(name), gridRef(grid)
{
    lastMoveTime = 0.0;
    segments.clear();
    int startGridX = 10;
    int startGridY = 10;
    for (size_t i = 0; i < length; ++i)
    {
        segments.push_back(SnakeSegment(startGridX, startGridY + i, gridRef.gridSize, snakeColor));
    }
    for (auto &segment : segments) segment.syncRect(gridRef.gridSize);
}

// --- Core game loop methods ---

void Snake::update()
{
    moved = false;
    if (gridRef.sizeChanged)
    {
        for (auto &segment : segments) segment.syncRect(gridRef.gridSize);
        gridRef.sizeChanged = false;
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
        positions.push_back({static_cast<float>(seg.gridX), static_cast<float>(seg.gridY)});
    return positions;
}

void Snake::handleInput(int keyPressed)
{
    if ((keyPressed == KEY_UP || keyPressed == KEY_W) && snakeHeadDirection != DOWN)
        snakeHeadDirection = UP;
    else if ((keyPressed == KEY_DOWN || keyPressed == KEY_S) && snakeHeadDirection != UP)
        snakeHeadDirection = DOWN;
    else if ((keyPressed == KEY_LEFT || keyPressed == KEY_A) && snakeHeadDirection != RIGHT)
        snakeHeadDirection = LEFT;
    else if ((keyPressed == KEY_RIGHT || keyPressed == KEY_D) && snakeHeadDirection != LEFT)
        snakeHeadDirection = RIGHT;
}

void Snake::move()
{
    if (segments.empty())
        return;
    std::vector<std::pair<int, int>> prevPositions;
    for (const auto &seg : segments)
        prevPositions.push_back({seg.gridX, seg.gridY});
    switch (snakeHeadDirection)
    {
    case UP:
        segments[0].gridY -= 1;
        break;
    case DOWN:
        segments[0].gridY += 1;
        break;
    case LEFT:
        segments[0].gridX -= 1;
        break;
    case RIGHT:
        segments[0].gridX += 1;
        break;
    }
    for (size_t i = 1; i < segments.size(); ++i)
        segments[i].gridX = prevPositions[i - 1].first, segments[i].gridY = prevPositions[i - 1].second;
    for (auto &segment : segments) segment.syncRect(gridRef.gridSize);
}

void Snake::wrapPos()
{
    int maxGridX = GetScreenWidth() / gridRef.gridSize;
    int maxGridY = GetScreenHeight() / gridRef.gridSize;
    if (segments[0].gridX < 0)
        segments[0].gridX = maxGridX - 1;
    else if (segments[0].gridX >= maxGridX)
        segments[0].gridX = 0;
    if (segments[0].gridY < 0)
        segments[0].gridY = maxGridY - 1;
    else if (segments[0].gridY >= maxGridY)
        segments[0].gridY = 0;
    segments[0].syncRect(gridRef.gridSize);
}

bool Snake::isIntact() const
{
    for (size_t i = 1; i < segments.size(); ++i)
    {
        int dx = segments[i].gridX - segments[i - 1].gridX;
        int dy = segments[i].gridY - segments[i - 1].gridY;
        if (abs(dx) > 1 || abs(dy) > 1)
            return false;
        bool adjacent = (abs(dx) == 1 && dy == 0) || (abs(dy) == 1 && dx == 0);
        if (!adjacent)
            return false;
        int maxGridX = GetScreenWidth() / gridRef.gridSize;
        int maxGridY = GetScreenHeight() / gridRef.gridSize;
        if (segments[i].gridX < 0 || segments[i].gridX >= maxGridX ||
            segments[i].gridY < 0 || segments[i].gridY >= maxGridY ||
            segments[i - 1].gridX < 0 || segments[i - 1].gridX >= maxGridX ||
            segments[i - 1].gridY < 0 || segments[i - 1].gridY >= maxGridY)
            return false;
    }
    return true;
}

void Snake::printScore()
{
    std::cout << score << std::endl;
}

// --- Getters/Setters ---

void Snake::grow()
{
    // Add new segment at the tail's position
    const SnakeSegment &tail = segments.back();
    segments.push_back(SnakeSegment(tail.gridX, tail.gridY, gridRef.gridSize, tail.color));
    ++length;
}
