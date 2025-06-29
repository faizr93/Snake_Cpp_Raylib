#include "utils.h"
#include <algorithm>

std::vector<int> getFactors(int value)
{
    std::vector<int> factors;
    for (int i = 1; i <= value; ++i)
    {
        if (value % i == 0)
            factors.push_back(i);
    }
    return factors;
}
std::vector<int> getCommonFactors(int a, int b)
{
    std::vector<int> factorsA = getFactors(a);
    std::vector<int> factorsB = getFactors(b);

    std::vector<int> common;
    for (int fa : factorsA)
    {
        if (std::find(factorsB.begin(), factorsB.end(), fa) != factorsB.end())
            common.push_back(fa);
    }

    return common;
}