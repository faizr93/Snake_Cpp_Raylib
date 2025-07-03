#include "foodHandler.h"

#include <vector>
#include <algorithm>
#include <raylib-cpp.hpp>

#include "utils.h"
#include "grid.h"
#include "snake.h"
#include "food.h"

// Constructor to The Food handler Class
FoodHandler::FoodHandler(Snake &snake, Grid &grid)
    : gridRef(grid), snakeRef(snake)
{
    foods.clear();
    for (int i = 0; i < maxFoodCount; ++i)
    {
        raylib::Vector2 pos = getRandPosWithinScreen();
        foods.push_back(Food(static_cast<int>(pos.x), static_cast<int>(pos.y), gridRef.gridSize));
        foods.back().syncRect(gridRef.gridSize);
    }
}

// Checks All Grid(Grid Positions) within Screen for a Spot Available for Food, Excludes SnakePos
raylib::Vector2 FoodHandler::getRandPosWithinScreen()
{
    std::vector<raylib::Vector2> snakePos = snakeRef.getSnakePos();
    raylib::Vector2 randomPos;
    int maxGridX = GetScreenWidth() / gridRef.gridSize;
    int maxGridY = GetScreenHeight() / gridRef.gridSize;
    do
    {
        randomPos.x = static_cast<float>(GetRandomValue(0, maxGridX - 1));
        randomPos.y = static_cast<float>(GetRandomValue(0, maxGridY - 1));
    } while (std::find(snakePos.begin(), snakePos.end(), randomPos) != snakePos.end());
    return randomPos;
}

// If snake moved, checks all Food for collision, Calls Reuse to recycle eaten food
void FoodHandler::handleCollision()
{
    if (snakeRef.moved)
    {
        raylib::Vector2 headPos = snakeRef.getHeadPos();
        for (auto &food : foods)
        {
            if (headPos.x == food.gridX && headPos.y == food.gridY)
            {
                food.isEaten = true;
                snakeRef.grow();
                snakeRef.score += food.scoreValue;
                reuseEaten(food);
            }
        }
    }
}


// --- Core Game Function ---
void FoodHandler::update()
{
    if (gridRef.sizeChanged) {
        for (auto& food : foods) food.syncRect(gridRef.gridSize);
        gridRef.sizeChanged = false; // Mark as handled
    }
    handleCollision();
    adaptCountToGrid();
    adaptFoodsVecToCount();
}
void FoodHandler::render() const
{
    for (const auto &food : foods)
    {
        food.render();
    }
}

// Takes in Food, Checks if Eaten, Assigns it a new position to eaten food
void FoodHandler::reuseEaten(Food& food)
{
    // Find a new random position not occupied by the snake or other food
    std::vector<raylib::Vector2> snakePos = snakeRef.getSnakePos();
    std::vector<raylib::Vector2> foodPos;
    for (const auto& f : foods) {
        if (&f != &food && !f.isEaten) {
            foodPos.push_back({static_cast<float>(f.gridX), static_cast<float>(f.gridY)});
        }
    }
    raylib::Vector2 pos;
    bool conflict;
    int maxGridX = GetScreenWidth() / gridRef.gridSize;
    int maxGridY = GetScreenHeight() / gridRef.gridSize;
    do {
        pos.x = static_cast<float>(GetRandomValue(0, maxGridX - 1));
        pos.y = static_cast<float>(GetRandomValue(0, maxGridY - 1));
        conflict = false;
        if (std::find(snakePos.begin(), snakePos.end(), pos) != snakePos.end()) conflict = true;
        if (std::find(foodPos.begin(), foodPos.end(), pos) != foodPos.end()) conflict = true;
    } while (conflict);
    food.gridX = static_cast<int>(pos.x);
    food.gridY = static_cast<int>(pos.y);
    food.isEaten = false;
    food.syncRect(gridRef.gridSize);
}

// Always assures the Food quantity is appropriate for GridSize
void FoodHandler::adaptCountToGrid()
{
    maxFoodCount = static_cast<int>(round(gridRef.gridSize / 3.0));
}

// Fills or Empties the Food Vector based on Needed Food Count on the grid
void FoodHandler::adaptFoodsVecToCount()
{
    while (foods.size() > static_cast<size_t>(maxFoodCount))
    {
        foods.pop_back();
    }
    while (foods.size() < maxFoodCount)
    {
        raylib::Vector2 pos = getRandPosWithinScreen();
        foods.push_back(Food(static_cast<int>(pos.x), static_cast<int>(pos.y), gridRef.gridSize));
        foods.back().syncRect(gridRef.gridSize);
    }
}