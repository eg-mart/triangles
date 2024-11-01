#pragma once

#include <variant>
#include "vector3.h"

namespace geometry {
struct segment_t {
public:
    using intersection_t = typename std::variant<std::monostate,
                                                 vector3_t, segment_t>;

    segment_t(const vector3_t& begin, const vector3_t& end);

    intersection_t intersect(const segment_t& rhs) const;
    bool is_parallel(const segment_t& other) const;
    bool is_point_on_segment(const vector3_t& point) const;

    bool operator==(const segment_t& rhs) const;

    vector3_t begin, end;
};
}
