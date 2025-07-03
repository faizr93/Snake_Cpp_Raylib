#ifndef SNAKE_CPP_RAYLIB_GRID_H_
#define SNAKE_CPP_RAYLIB_GRID_H_

#include <vector>

#include "gameObject.h"

class Grid : public GameObject
{
public:
    bool  sizeChanged;
    float gridSize;

    Grid(float gridSize = 25.0f);

    std::vector<int> getCommonScreenFactors();
    std::vector<int> getClampedFactors(const std::vector<int>& factors, int min, int max);

    std::vector<int> gridSizes         = getClampedFactors(getCommonScreenFactors(), 10, 50);
    int              gridSizesIterator = static_cast<int>(gridSizes.size()) / 2;

    void handleInput(int keyPressed);
    void update() override;
    void render() const override;
    void printGridSize() const;
};

#endif // SNAKE_CPP_RAYLIB_GRID_H_