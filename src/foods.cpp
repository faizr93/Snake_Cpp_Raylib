#include <raylib-cpp.hpp>
#include <algorithm>
#include "foods.h"
#include "utils.h"
#include "grid.h"

raylib::Vector2 FoodHandler::getRandPosWithinScreen()
{
    raylib::Vector2 randomPos;
    std::vector<raylib::Vector2> snakePos = snakeRef.getSnakePos();

    do
    {
        randomPos.x = static_cast<float>(GetRandomValue(0, GetScreenWidth()));
        randomPos.y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
        snapToGrid(randomPos.x, Grid::gridSize);
        snapToGrid(randomPos.y, Grid::gridSize);
    } while (std::find(snakePos.begin(), snakePos.end(), randomPos) != snakePos.end());

    return randomPos;
}

void FoodHandler::render() const
{
    for (auto &food : foods)
    {
        food.rect.Draw(food.color);
    }
}

Food::Food(Rectangle rect, raylib::Color color, int scoreValue)
    : rect(rect), color(color), scoreValue(scoreValue) {}

void Food::onCollision(Snake &snake)
{
    snake.grow();
    snake.score += scoreValue;
    isEaten = true; // mark for deletion
}

FoodHandler::FoodHandler(Snake &s)
    : snakeRef(s)
{
    foods.clear();
    Food normalFood;
    for (size_t i = 0; i < maxFoodCount; i++)
    {
        foods.push_back(normalFood);
    }
}

raylib::Vector2 FoodHandler::collisionCheck(raylib::Vector2 foodPos)
{
    return snakeRef.getHeadPos() == foodPos;
}

void FoodHandler::handleCollision()
{
    
}

void FoodHandler::update()
{
    reuseEaten();
    adaptCountToGrid();
    adaptFoodsToCount();
};

void FoodHandler::reuseEaten()
{

    for (auto &food : foods)
    {
        if (food.isEaten == true)
        {
            food.rect.SetPosition(getRandPosWithinScreen());
            food.isEaten == false;
        }
    }
}
void FoodHandler::adaptCountToGrid()
{
    maxFoodCount = static_cast<int>(round(Grid::gridSize / 3.0));
}
void FoodHandler::adaptFoodsToCount()
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