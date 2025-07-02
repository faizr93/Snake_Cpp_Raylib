#include <raylib-cpp.hpp>
#include <algorithm>
#include "foods.h"
#include "utils.h"
#include "grid.h"

// ---Food Class Methods---

//Constructor
Food::Food(Grid& grid, Rectangle rec, raylib::Color color, int scoreValue)
    : gridRef(grid), rect(rec), color(color), scoreValue(scoreValue)
{
    // If rect width/height are 0, set them to gridRef.gridSize
    if (rect.width == 0 || rect.height == 0) {
        rect.width  = gridRef.gridSize;
        rect.height = gridRef.gridSize;
    }
}
//Takes a Reference to Snake and checks collision with it, marks food as eaten and calls grow and increases score
void Food::handleCollision(Snake &snake)
{
    snake.grow();
    snake.score += scoreValue;
    isEaten = true;
}

//Constructor to The Food handler Class
FoodHandler::FoodHandler(Snake &snake,Grid& grid)
    : gridRef(grid), snakeRef(snake)
{
    foods.clear();
    Food normalFood;
    for (int i = 0; i < maxFoodCount; ++i)
    {
        foods.push_back(normalFood);
    }
}

//Checks All Grid within Screen for a Spot Available for Food, Excludes SnakePos
raylib::Vector2 FoodHandler::getRandPosWithinScreen()
{
    raylib::Vector2 randomPos;
    std::vector<raylib::Vector2> snakePos = snakeRef.getSnakePos();

    do
    {
        randomPos.x = static_cast<float>(GetRandomValue(0, GetScreenWidth()));
        randomPos.y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
        snapToGrid(randomPos.x, gridRef.gridSize);
        snapToGrid(randomPos.y, gridRef.gridSize);
    } while (std::find(snakePos.begin(), snakePos.end(), randomPos) != snakePos.end());

    return randomPos;
}



// Check if given foodPos == Referenced snakeHeadPos
bool FoodHandler::checkCollision(raylib::Vector2 foodPos)
{
    return snakeRef.getHeadPos() == foodPos;
}

// If snake moved, checks all Food for collision, and calls handleCollision of the collied food, Calls Reuse to recycle eaten food
void FoodHandler::handleCollision()
{
    if (snakeRef.moved)
    {
        for (auto &food : foods)
        {
            if (checkCollision(food.rect.GetPosition()))
            {
                food.handleCollision(snakeRef);
            }
            reuseEaten(food);
        }
    }
}
// --- Core Game Function ---
void FoodHandler::update()
{
    handleCollision();
    adaptCountToGrid();
    adaptFoodsVecToCount();
}
void FoodHandler::render() const
{
    for (const auto &food : foods)
    {
        food.rect.Draw(food.color);
    }
}

// Takes in Food, Checks if Eaten, Assigns it a new position to eaten food
void FoodHandler::reuseEaten(Food food)
{
    if (food.isEaten)
    {
        food.rect.SetPosition(getRandPosWithinScreen());
        food.isEaten = false;
    }
}

//Always assures the Food quantity is appropriate for GridSize
void FoodHandler::adaptCountToGrid()
{
    maxFoodCount = static_cast<int>(round(gridRef.gridSize / 3.0));
}

//Fills or Empties the Food Vector based on Needed Food Count on the grid
void FoodHandler::adaptFoodsVecToCount()
{
    std::vector<raylib::Vector2> snakePos = snakeRef.getSnakePos();
    if (foods.size() > static_cast<size_t>(maxFoodCount))
    {
        foods.resize(maxFoodCount);
    }
    else if (foods.size() < maxFoodCount)
    {
        Food newFood;
        newFood.rect.SetPosition(getRandPosWithinScreen());
        foods.push_back(newFood);
    }
}