#include <cmath>

#include "common.h"

namespace geometry{
bool is_equal_double(double x, double y)
{
    return std::abs(x - y) < EPSILON;
}
}
