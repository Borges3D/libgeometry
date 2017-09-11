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

const bool
is_definitely_less(const Point_2& p1, const Point_2& p2)
{
    if (is_definitely_less(p1.x(), p2.x())) {
        return true;
    }
    if (is_definitely_less(p2.x(), p1.x())) {
        return false;
    }
    return is_definitely_less(p1.y(), p2.y());
}

const Point_2
operator+(const Point_2& p, const Vector_2& v)
{
    return Point_2(p.x() + v.x(), p.y() + v.y());
}

const Point_2
operator-(const Point_2& p, const Vector_2& v)
{
    return Point_2(p.x() - v.x(), p.y() - v.y());
}

const Vector_2
operator-(const Point_2& p1, const Point_2& p2)
{
    return Vector_2(p1.x() - p2.x(), p1.y() - p2.y());
}

const double
squared_distance(const Point_2& p1, const Point_2& p2)
{
    return squared_length(p2 - p1);
}

} // namespace Geometry
