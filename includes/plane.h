#pragma once

#include "vector3.h"

namespace geometry {
struct plane_t
{
public:
    plane_t(const vector3_t& norm, const vector3_t& orig);
    plane_t(const vector3_t& a, const vector3_t& b, const vector3_t& c);

    bool is_point_on_plane(const vector3_t& point) const;

    vector3_t normal, origin;
};
}
