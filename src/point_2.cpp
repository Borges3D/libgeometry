#include "point_2.h"

namespace Geometry {

Point_2::Point_2(const double x, const double y) : x_(x), y_(y)
{
}

const double&
Point_2::x() const
{
    return x_;
}

const double&
Point_2::y() const
{
    return y_;
}

double
distance(const Point_2& p1, const Point_2& p2)
{
    return length(p2 - p1);
}

Vector_2
operator-(const Point_2& p1, const Point_2& p2)
{
    return Vector_2(p1.x() - p2.x(), p2.y() - p1.y());
}

} // namespace Geometry
