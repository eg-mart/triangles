#include <cmath>

#include "common.h"

namespace geometry{
bool eq_double(double x, double y)
{
    return std::abs(x - y) < EPSILON;
}

bool lt_double(double x, double y)
{
    return (x + EPSILON) < y;
}

bool gt_double(double x, double y)
{
    return x > (y + EPSILON);
}

bool lte_double(double x, double y)
{
    return eq_double(x, y) || lt_double(x, y);
}

bool gte_double(double x, double y)
{
    return eq_double(x, y) || gt_double(x, y);
}
}
