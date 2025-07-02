#pragma once

#include <raylib-cpp.hpp>
#include "gameObject.h"
#include "interfaces.h"
#include "snake.h"

struct Food : public ICollideable {
    bool              isEaten    = false;
    int               scoreValue;
    raylib::Rectangle rect;
    raylib::Color     color;

    Food(
        Rectangle rect = {0, 0, Grid::gridSize, Grid::gridSize},
        raylib::Color color = BLUE,
        int scoreValue = 1
    );

    void onCollision(Snake& snake) override;
};

class FoodHandler : public GameObject {
protected:
    std::vector<Food> foods;
    int               maxFoodCount;

public:
    FoodHandler(Snake& s  = *(Snake*)nullptr);
    Snake& snakeRef;

    raylib::Vector2 collisionCheck(
        raylib::Vector2 foodPos
    );

    void handleCollision();
    void reuseEaten();
    void adaptFoodsToCount();
    void adaptCountToGrid(); // Updates maxFoodCount according to Grid Size

    void update() override = 0;
    void update();
    void render() const override;

    raylib::Vector2 getRandPosWithinScreen();
};