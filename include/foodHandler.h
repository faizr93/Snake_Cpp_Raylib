#ifndef SNAKE_CPP_RAYLIB_FOOD_HANDLER_H_
#define SNAKE_CPP_RAYLIB_FOOD_HANDLER_H_

#include <vector>
#include <raylib-cpp.hpp>

#include "food.h"
#include "grid.h"
#include "snake.h"
#include "gameObject.h"

class FoodHandler : public GameObject
{
public:
    FoodHandler(Snake& s, Grid& gridRef);
    Snake& snakeRef;
    Grid& gridRef;
    void update() override;
    void render() const override;

    void handleCollision();
    void reuseEaten(Food& food);
    void adaptFoodsVecToCount();
    void adaptCountToGrid();
    raylib::Vector2 getRandPosWithinScreen();

protected:
    std::vector<Food> foods;
    int               maxFoodCount;
};

#endif //SNAKE_CPP_RAYLIB_FOOD_HANDLER_H_