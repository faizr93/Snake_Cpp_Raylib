#ifndef SNAKE_CPP_RAYLIB_FOODS_H_
#define SNAKE_CPP_RAYLIB_FOODS_H_

#include <raylib-cpp.hpp>
#include "gameObject.h"
#include "interfaces.h"
#include "snake.h"

struct Food : public ICollideable
{
    bool              isEaten    = false;
    int               scoreValue;
    raylib::Rectangle rect;
    raylib::Color     color;
    Grid& gridRef;

    Food(
        Grid& gridRef = *(Grid*)nullptr,
        Rectangle rect = {0, 0, 0, 0}, // Use a constant or 0 here
        raylib::Color color = BLUE,
        int scoreValue = 1
    );

    void handleCollision(Snake& snake) override;
};

class FoodHandler : public GameObject
{
public:
    FoodHandler(Snake& s = *(Snake*)nullptr, Grid& gridRef = *(Grid*)nullptr);
    Snake& snakeRef;
    Grid& gridRef;
    void update() override;
    void render() const override;

    bool checkCollision(raylib::Vector2 foodPos);
    void handleCollision();
    void reuseEaten(Food food);
    void adaptFoodsVecToCount();
    void adaptCountToGrid();
    raylib::Vector2 getRandPosWithinScreen();

protected:
    std::vector<Food> foods;
    int               maxFoodCount;
};

#endif // SNAKE_CPP_RAYLIB_FOODS_H_