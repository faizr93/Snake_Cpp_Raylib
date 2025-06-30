#pragma once
#include <vector>

const std::vector<int> getFactors(int value);
const std::vector<int> getCommonFactors(int a,int b);
void snapToGrid(float& valueToSnap, float gridToSnapTo); // Pass by reference