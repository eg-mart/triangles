#include <iostream>
#include "vector3.h"

int main()
{
    auto x = geometry::vector3_t(2, 2, 0);
    auto y = geometry::vector3_t(2, 2, 0);
    auto cross = x.cross(y);
    auto dot = x.dot(y);
    std::cout << x << " " << y << " " << cross << " " << dot << " ";
    x.normalize();
    std::cout << x << " " << x.mod() << std::endl;

    return 0;
}
