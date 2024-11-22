#pragma once

#include <variant>
#include "vector3.h"
#include "segment.h"
#include "plane.h"

namespace geometry {
struct triangle_t
{
public:
    triangle_t(const vector3_t& a, const vector3_t& b, const vector3_t& c);
    
    bool is_intersecting(const triangle_t& other) const;
    bool is_point_on_triangle(const vector3_t& point) const;

    vector3_t p[3];
    bool is_intersect = 0;

private:
    bool intersect_lines_with_plane_(const triangle_t& other) const;
};
}
