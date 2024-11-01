#pragma once

#include <ostream>

namespace geometry {
struct vector3_t
{
public:
    vector3_t();
    vector3_t(double x, double y, double z);

    bool  operator==(const vector3_t& rhs) const;
    bool  operator!=(const vector3_t& rhs) const;
    vector3_t& operator-=(const vector3_t& rhs);
    vector3_t& operator+=(const vector3_t& rhs);
    vector3_t  cross     (const vector3_t& rhs) const;
    double     dot       (const vector3_t& rhs) const;
    double     mod       () const;
    void       normalize ();
    bool is_collinear(const vector3_t& other) const;

    friend vector3_t operator- (vector3_t lhs, const vector3_t& rhs);
    friend vector3_t operator- (vector3_t lhs);
    friend vector3_t operator+ (vector3_t lhs, const vector3_t& rhs);
    friend vector3_t operator* (double lhs, vector3_t rhs);
    friend std::ostream& operator<<(std::ostream& os, const vector3_t& obj);

    double x[3] = {0, 0, 0}; 
};
}
