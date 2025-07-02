#pragma once
#include "snakeSegment.h"
#include "gameObject.h"

// Snake class handles the snake's state, movement, and rendering
class Snake : public GameObject
{
public:
    // --- Construction ---
    std::string playerName; // when 1 snake
    int score;
    int highScore;
    
    Snake(std::string name = "Player1", int length = 7, raylib::Color snakeColor = GREEN);

    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    // --- Core game loop methods ---
    void update() override;
    void render() const override;

    // --- Input and mechanics ---
    const std::vector<raylib::Vector2> getSnakePos();
    void handleInput();
    void move();
    void scale();
    void wrapPos();
    void snapSnakeToGrid();
    bool isIntact() const;

    // --- State ---
    std::vector<SnakeSegment> segments;
    Direction snakeHeadDirection = UP;

    // --- Getters/Setters---
    const raylib::Vector2 getHeadPos();
    void setHeadPos(Vector2 pos);

    // --- Internal helpers ---
    void grow();
    private:

    // --- Config ---
    int length = 7;
};