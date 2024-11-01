#include <cassert>
#include "plane.h"
#include "common.h"

namespace geometry {
plane_t::plane_t(const vector3_t& norm, const vector3_t& orig)
    : normal(norm)
    , origin(orig)
{
    assert(!is_equal_double(norm.mod(), 0));
    normal.normalize();
}

plane_t::plane_t(const vector3_t& a, const vector3_t& b, const vector3_t& c)
{
    vector3_t u = b - a;
    vector3_t v = c - a;

    normal = u.cross(v);
    normal.normalize();
    
    assert(!is_equal_double(normal.mod(), 0));

    origin = a.dot(normal) * normal;
}

bool plane_t::is_point_on_plane(const vector3_t& point) const
{
    double d = -normal.dot(origin);
    return is_equal_double(normal.dot(point) + d, 0);
}
}
