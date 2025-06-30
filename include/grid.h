#pragma once
#include "gameObject.h"
#include <vector>

class Grid : public GameObject
{
public:
    static bool  isScaling;
    static float gridSize;

    Grid();

    std::vector<int> getCommonScreenFactors();
    std::vector<int> getClampedFactors(const std::vector<int>& factors, int min, int max);

    std::vector<int> gridSizes         = getClampedFactors(getCommonScreenFactors(), 10, 50);
    int              gridSizesIterator = static_cast<int>(gridSizes.size()) / 2; // Start in the middle

    void handleInput();
    void update() override;
    void render() const override;
};