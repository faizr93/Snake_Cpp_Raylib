#ifndef SNAKE_CPP_RAYLIB_SNAKE_H_
#define SNAKE_CPP_RAYLIB_SNAKE_H_

#include <string>
#include <vector>
#include <raylib-cpp.hpp>

#include "snakeSegment.h"
#include "gameObject.h"
#include "grid.h"

// Snake class handles the snake's state, movement, and rendering
class Snake : public GameObject
{
public:
    // --- Construction ---
    int score;
    int highScore;
    bool moved;
    double lastMoveTime;
    std::string playerName;
    const double moveInterval = 0.17;
    Grid &gridRef;

    Snake(Grid &gridRef, std::string name = "Player1", int length = 7, raylib::Color snakeColor = GREEN);

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
    void handleInput(int keyPressed);
    void move();
    void scale(); // Will be removed in implementation
    void wrapPos();
    void snapSnakeToGrid(); // Will be removed in implementation
    void printScore();
    
    // --- Internal helpers ---
    void grow();
    bool isIntact() const;

    // --- State ---
    std::vector<SnakeSegment> segments;
    Direction snakeHeadDirection = UP;

    // --- Getters/Setters ---
    const raylib::Vector2 getHeadPos()
    {
        return {static_cast<float>(segments[0].gridX), static_cast<float>(segments[0].gridY)};
    }

    void setHeadPos(Vector2 newPos)
    {
        segments[0].gridX = static_cast<int>(newPos.x);
        segments[0].gridY = static_cast<int>(newPos.y);
        segments[0].syncRect(gridRef.gridSize);
    }

    

private:
    int length = 7;
};
#endif // SNAKE_CPP_RAYLIB_SNAKE_H_