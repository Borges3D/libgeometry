#include "point_3.h"
#include "scalar.h"

namespace Geometry {

Point_3::Point_3(const double x, const double y, const double z)
    : x_(x), y_(y), z_(z)
{
}

const double&
Point_3::x() const
{
    return x_;
}

const double&
Point_3::y() const
{
    return y_;
}

const double&
Point_3::z() const
{
    return z_;
}

const double
distance(const Point_3& p1, const Point_3& p2)
{
    return length(p2 - p1);
}

const bool
is_approximately_equal(const Point_3& p1, const Point_3& p2)
{
    if (!is_approximately_equal(p1.x(), p2.x())) {
        return false;
    }
    if (!is_approximately_equal(p1.y(), p2.y())) {
        return false;
    }
    return is_approximately_equal(p1.z(), p2.z());
}

const bool
is_definitely_less(const Point_3& p1, const Point_3& p2)
{
    if (is_definitely_less(p1.x(), p2.x())) {
        return true;
    }
    if (is_definitely_less(p2.x(), p1.x())) {
        return false;
    }
    if (is_definitely_less(p1.y(), p2.y())) {
        return true;
    }
    if (is_definitely_less(p2.y(), p1.y())) {
        return false;
    }
    return is_definitely_less(p1.z(), p2.z());
}

const Point_3
operator+(const Point_3& p, const Vector_3& v)
{
    return Point_3(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}

const Point_3
operator-(const Point_3& p, const Vector_3& v)
{
    return Point_3(p.x() - v.x(), p.y() - v.y(), p.z() - v.z());
}

const Vector_3
operator-(const Point_3& p1, const Point_3& p2)
{
    return Vector_3(p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z());
}

const double
squared_distance(const Point_3& p1, const Point_3& p2)
{
    return squared_length(p2 - p1);
}

} // namespace Geometry
