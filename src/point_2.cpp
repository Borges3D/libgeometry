#include "point_2.h"
#include "utilities.h"

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

const double
distance(const Point_2& p1, const Point_2& p2)
{
    return length(p2 - p1);
}

const bool
is_approximately_equal(const Point_2& p1, const Point_2& p2)
{
    if (!is_approximately_equal(p1.x(), p2.x())) {
        return false;
    }
    return is_approximately_equal(p1.y(), p2.y());
}

const Vector_2
operator-(const Point_2& p1, const Point_2& p2)
{
    return Vector_2(p1.x() - p2.x(), p1.y() - p2.y());
}

} // namespace Geometry
