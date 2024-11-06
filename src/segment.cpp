#include <algorithm>
#include <cassert>
#include "segment.h"
#include "common.h"

namespace geometry {
segment_t::segment_t(const vector3_t& begin, const vector3_t& end)
    : begin(begin)
    , end(end)
{
    assert(begin != end);
}

segment_t::intersection_t segment_t::intersect(const segment_t& rhs) const
{
    // Finding lines, on which these segments lie, in the form of
    // vec3(a) * t + vec3(b)
    vector3_t a1 = end - begin;
    vector3_t a2 = rhs.end - rhs.begin;
    double length1 = a1.mod();
    double length2 = a1.mod(); 

    vector3_t b1 = begin;
    vector3_t b2 = rhs.begin;
    vector3_t b_diff = b2 - b1;

    if (a1.is_collinear(a2) && a1.is_collinear(b_diff)) {
        double begin_param1 = 0;
        double end_param1 = 1;
        double begin_param2 = (rhs.begin - b1).dot(a1) / length1;
        double end_param2 = (rhs.end - b1).dot(a1) / length1;

        if (begin_param2 > end_param2)
            std::swap(begin_param2, end_param2);

        // If the segments lie one after another and don't intersect
        if (std::max(begin_param1, begin_param2) >
            std::min(end_param1, end_param2)) {
            return std::monostate();
        }

        // If the end points of two segments match
        if (is_equal_double(std::max(begin_param1, begin_param2),
                            std::min(end_param1, end_param2))) {
            return std::max(begin_param1, begin_param2) * a1 + b1;
        }

        // If the segments intersect, forming another segment
        vector3_t intersect_begin = std::max(begin_param1, begin_param2) * a1 + b1;
        vector3_t intersect_end = std::min(end_param1, end_param2) * a1 + b1;

        return segment_t(intersect_begin, intersect_end); 
    } else if (!is_equal_double(a1.cross(a2).dot(b_diff), 0) ||
               a1.is_collinear(a2)) {
        // If the lines lie in different planes or are parallel
        return std::monostate();
    }
    
    vector3_t h = a2.cross(b_diff);
    vector3_t k = a2.cross(a1);
    
    int sign = 0;
    if (h.dot(k) > 0)
        sign = 1;
    else
        sign = -1;
    
    double intersection_param1 = sign * h.mod() / k.mod();

    if (intersection_param1 < 0 || intersection_param1 > 1)
        return std::monostate();

    return b1 + intersection_param1 * a1;
}

bool segment_t::is_parallel(const segment_t& other) const
{
    vector3_t a1 = end - begin;
    vector3_t a2 = other.end - other.begin;
    return a1.is_collinear(a2);
}

bool segment_t::is_point_on_segment(const vector3_t& point) const
{
    vector3_t a = end - begin;
    double point_param = point.dot(a) / a.mod();
    return a.is_collinear(point - begin) &&
           gt_double(point_param, 0) &&
           lt_double(point_param, 1);
}

bool segment_t::operator==(const segment_t& rhs) const
{
    return (begin == rhs.begin && end == rhs.end);
}
}
