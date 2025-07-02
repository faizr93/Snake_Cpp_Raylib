#ifndef SNAKE_CPP_RAYLIB_UTILS_H_
#define SNAKE_CPP_RAYLIB_UTILS_H_

#include <vector>

std::vector<int> getFactors(int value);
std::vector<int> getCommonFactors(int a, int b);
void snapToGrid(float& valueToSnap, float gridToSnapTo);

#endif // SNAKE_CPP_RAYLIB_UTILS_H_