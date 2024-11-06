#include "intersections.h"
#include "common.h"

namespace geometry {
segment_plane_intersection_t segment_plane_intersect(
    const segment_t& segment, const plane_t& plane)
{
    // Finding lines, on which the segment lies, in the form of
    // vec3(a) * t + vec3(b)
    // Note that a and b are perpendicular
    vector3_t a = segment.end - segment.begin;
    vector3_t b = segment.begin;

    // Plane is represented by the equation
    // vec3(n) * vec3(x) + d = 0
    double d = -plane.normal.dot(plane.origin);

    // If n and a are perpendicular, then either plane and segment are parallel
    // or segment lies in the plane
    if (eq_double(plane.normal.dot(a), 0)) {
        if (eq_double(plane.normal.dot(b) + d, 0))
            return segment;
        return std::monostate();
    }

    double intersection_param = (-d - plane.normal.dot(b)) / plane.normal.dot(a);

    if (intersection_param < 0 || intersection_param > 1)
        return std::monostate();

    return intersection_param * a + b;
}
}
