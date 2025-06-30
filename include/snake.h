#pragma once
#include "snakeSegment.h"
#include "gameObject.h"

// Snake class handles the snake's state, movement, and rendering
class Snake : public GameObject
{
public:
    // --- Construction ---
    Snake();

    // --- Core game loop methods ---
    void update() override;
    void render() const override;

    // --- Input and mechanics ---
    void handleInput();
    void move();
    void scale();
    void wrapPos();
    void snapSnakeToGrid();
    bool isIntact() const;

    // --- State ---
    std::vector<SnakeSegment> segments;
    GameObject::Direction snakeHeadDirection = UP;

private:
    // --- Internal helpers ---
    void init();
    void grow();

    // --- Config ---
    int length = 7;
};