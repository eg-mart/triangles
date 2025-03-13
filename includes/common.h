namespace geometry{

const double EPSILON = 1e-5;

inline bool eq_double(double x, double y) // is equal
{
    return std::abs(x - y) < EPSILON;
}

inline bool lt_double(double x, double y)  // is less than
{
    return (x + EPSILON) < y;
}

inline bool gt_double(double x, double y)  // is greater than
{
    return x > (y + EPSILON);
}

inline bool lte_double(double x, double y) // is less than or equal
{
    return eq_double(x, y) || lt_double(x, y);
}

inline bool gte_double(double x, double y) // is greater than or equal
{
    return eq_double(x, y) || gt_double(x, y);
}

}
