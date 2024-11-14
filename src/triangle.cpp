#include <vector>
#include "triangle.h"
#include "common.h"
#include "intersections.h"

namespace geometry {
    triangle_t::triangle_t(const vector3_t& a, const vector3_t& b, const vector3_t& c)
        : p{a, b, c}
    {}

    bool triangle_t::is_intersecting(const triangle_t& other) const
    {
        if (intersect_lines_with_plane_(other))
            return true;

        if (other.intersect_lines_with_plane_(*this))
            return true;

        return false; 
    }

    bool triangle_t::is_point_on_triangle(const vector3_t& point) const
    {
        // if the triangle is degenerate and in reality is just a point
        if (p[0] == p[1] && p[1] == p[2])
            return point == p[0];

        std::vector<segment_t> lines;
        for (size_t i = 0; i < 3; i++)
            for (size_t j = i + 1; j < 3; j++)
                if (p[i] != p[j])
                    lines.push_back(segment_t(p[i], p[j]));

        // if the triangle is just a line
        if (lines[0].is_parallel(lines[1])) {
            for (auto it = lines.begin(); it != lines.end(); ++it)
                if (it->is_point_on_segment(point))
                    return true;
            return false;
        }

        plane_t triangle_plane = plane_t(p[0], p[1], p[2]);

        if (!triangle_plane.is_point_on_plane(point))
            return false;

        // vectors from point to triangle top
        vector3_t pa = point - p[0];
        vector3_t pb = point - p[1];
        vector3_t pc = point - p[2];

        // if the point inside triangle
        if (eq_double(pa.cross(pb).mod() + 
                      pa.cross(pc).mod() + 
                      pb.cross(pc).mod(),  
                      (p[0] - p[1]).cross(p[0] - p[2]).mod()))
            return true;
        return false;
    }

    bool triangle_t::intersect_lines_with_plane_(const triangle_t& other) const
    {
        // if this triangle is a point, check if it intersects with the 
        // other triangle
        if (p[0] == p[1] && p[1] == p[2])
            return other.is_point_on_triangle(p[0]);

        // if the other triangle is a point, no plane can be constructed - 
        // return false
        if (other.p[0] == other.p[1] && other.p[1] == other.p[2])
            return false;

        // TODO: switch from vectors to arrays (need for speed)

        std::vector<segment_t> this_lines;
        for (size_t i = 0; i < 3; i++)
            for (size_t j = i + 1; j < 3; j++)
                if (p[i] != p[j])
                    this_lines.push_back(segment_t(p[i], p[j]));

        std::vector<segment_t> other_lines;
        for (size_t i = 0; i < 3; i++)
            for (size_t j = i + 1; j < 3; j++)
                if (other.p[i] != other.p[j])
                    other_lines.push_back(segment_t(other.p[i], other.p[j]));

        // if both triangles are in fact lines, a different algorithm is needed
        if (this_lines[0].is_parallel(this_lines[1]) &&
                other_lines[0].is_parallel(other_lines[1])) {
            for (auto const &this_line : this_lines) {
                for (auto const &other_line : other_lines) {
                    auto intersection = this_line.intersect(other_line);
                    if (!std::holds_alternative<std::monostate>(intersection))
                        return true;
                }
            }
            return false;
                    
        // if the other triangle is a line, no plane can be constructed -
        // return false
        } else if (other_lines[0].is_parallel(other_lines[1])) {
            return false;
        }

        plane_t other_plane = plane_t(other.p[0], other.p[1], other.p[2]);
        
        for (auto const &this_line : this_lines) {
            auto intersection = segment_plane_intersect(this_line, other_plane);
            
            if (std::holds_alternative<vector3_t>(intersection))
                if (other.is_point_on_triangle(std::get<vector3_t>(intersection)))
                    return true;

            if (std::holds_alternative<segment_t>(intersection)) {
                for (auto const &other_line : other_lines) {
                    auto line_intersection = other_line.intersect(
                        std::get<segment_t>(intersection));
                    if (!std::holds_alternative<std::monostate>(line_intersection))
                        return true;
                }
            }
        }

        return false;
    }
}
