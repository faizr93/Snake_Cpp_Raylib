#include <raylib-cpp.hpp>
#include <algorithm>
#include "utils.h"

// --- Utility Functions ---

void snapToGrid(float& valueToSnap, float gridToSnapTo) {
    valueToSnap = roundf(valueToSnap / gridToSnapTo) * gridToSnapTo;
}

std::vector<int> getFactors(int value) {
    std::vector<int> factors;
    for (int i = 1; i <= value; ++i) {
        if (value % i == 0)
            factors.push_back(i);
    }
    return factors;
}

std::vector<int> getCommonFactors(int a, int b) {
    const std::vector<int> factorsA = getFactors(a);
    const std::vector<int> factorsB = getFactors(b);

    std::vector<int> common;
    for (int fac : factorsA) {
        if (std::find(factorsB.begin(), factorsB.end(), fac) != factorsB.end())
            common.push_back(fac);
    }
    return common;
}