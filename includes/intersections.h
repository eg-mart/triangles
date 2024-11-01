#pragma once

#include "plane.h"
#include "segment.h"
#include "vector3.h"

namespace geometry {
    using segment_plane_intersection_t = 
        typename std::variant<std::monostate, vector3_t, segment_t>;

    segment_plane_intersection_t segment_plane_intersect(
        const segment_t& segment, const plane_t& plane);
}
