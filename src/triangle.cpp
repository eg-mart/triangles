#include "triangle.h"
#include "common.h"

namespace geometry {
triangle_t::triangle_t(const vector3_t& a, const vector3_t& b, const vector3_t& c)
    : a(a)
    , b(b)
    , c(c)
{}

bool triangle_t::is_intersecting(const triangle_t& other) const
{
    return false; 
}

bool triangle_t::is_point_on_triangle(const vector3_t& point) const
{
    // if the triangle is degenerate and in reality is just a point
    if (a == b && b == c) {
        return (point == a || point == b || point == c);
    }

    segment_t ab = segment_t(a, b);
    segment_t ac = segment_t(a, c);
    segment_t bc = segment_t(b, c);

    // if the triangle is degenerate and in reality is just a segment
    if (ab.is_parallel(ac)) {
        return (ab.is_point_on_segment(point) || ac.is_point_on_segment(point) ||
                bc.is_point_on_segment(point));
    }

    plane_t triangle_plane = plane_t(a, b, c);
    if (!triangle_plane.is_point_on_plane(point)) {
        return false;
    }

    

    return false;
}
}
