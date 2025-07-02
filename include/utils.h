#pragma once
#include <vector>

namespace raylib{ // Forward Declaration
    class Vector2;
}

std::vector<int> getFactors(int value);
std::vector<int> getCommonFactors(int a, int b);
void snapToGrid(float& valueToSnap, float gridToSnapTo);