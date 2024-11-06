#include <iostream>
#include <cmath>
#include "vector3.h"
#include "common.h"

namespace geometry {
vector3_t::vector3_t() {};

vector3_t::vector3_t(double x, double y, double z) : x{x, y, z}
{};

bool vector3_t::operator==(const vector3_t& rhs) const
{
    bool equal = true;
    for (size_t i = 0; i < 3; i++)
        equal &= eq_double(rhs.x[i], x[i]);
    return equal;
}

bool vector3_t::operator!=(const vector3_t& rhs) const
{
    return !(*this == rhs);
}

vector3_t& vector3_t::operator-=(const vector3_t& rhs)
{
    for (size_t i = 0; i < 3; i++)
        x[i] -= rhs.x[i];

    return *this;
}

vector3_t& vector3_t::operator+=(const vector3_t& rhs)
{
    for (size_t i = 0; i < 3; i++)
        x[i] += rhs.x[i];

    return *this;
}

vector3_t vector3_t::cross(const vector3_t& rhs) const
{
    vector3_t res;
    res.x[0] = x[1] * rhs.x[2] - x[2] * rhs.x[1];
    res.x[1] = x[2] * rhs.x[0] - x[0] * rhs.x[2];
    res.x[2] = x[0] * rhs.x[1] - x[1] * rhs.x[0];

    return res;
}

double vector3_t::dot(const vector3_t& rhs) const
{
    double res = 0;
    for (size_t i = 0; i < 3; i++)
        res += x[i] * rhs.x[i];
    return res;
}

double vector3_t::mod() const
{
    double squared_mod = 0;
    for (size_t i = 0; i < 3; i++)
        squared_mod += x[i] * x[i];
    return sqrt(squared_mod);
}

void vector3_t::normalize()
{
    if (eq_double(mod(), 0))
        return;
    double coeff = 1 / mod();
    for (size_t i = 0; i < 3; i++)
        x[i] *= coeff;
}

bool vector3_t::is_collinear(const vector3_t& other) const
{
    return eq_double(cross(other).mod(), 0);
}

vector3_t operator-(vector3_t lhs, const vector3_t& rhs)
{
    lhs -= rhs;
    return lhs;
}

vector3_t operator-(vector3_t lhs)
{
    for (size_t i = 0; i < 3; i++)
        lhs.x[i] = -lhs.x[i];
    return lhs;
}

vector3_t operator+(vector3_t lhs, const vector3_t& rhs)
{
    lhs += rhs;
    return lhs;
}

vector3_t operator*(double lhs, vector3_t rhs)
{
    for (size_t i = 0; i < 3; i++)
        rhs.x[i] *= lhs;
    return rhs;
}

std::ostream& operator<<(std::ostream& os, const vector3_t& obj)
{
    os << "vec3(" << obj.x[0] << ", " << obj.x[1] << ", " << obj.x[2] << ")";
    return os;
}
}
