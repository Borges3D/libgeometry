#include "vector_2.h"
#include "point_2.h"
#include "scalar.h"
#include <cmath>

namespace Geometry {

Vector_2::Vector_2(const double x, const double y) : x_(x), y_(y)
{
}

const double&
Vector_2::x() const
{
    return x_;
}

const double&
Vector_2::y() const
{
    return y_;
}

const double
cross_product(const Vector_2& v1, const Vector_2& v2)
{
    return dot_product(v1, perpendicular(v2));
}

const double
dot_product(const Vector_2& v1, const Vector_2& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}

const bool
is_approximately_equal(const Vector_2& v1, const Vector_2& v2)
{
    if (!is_approximately_equal(v1.x(), v2.x())) {
        return false;
    }
    return is_approximately_equal(v1.y(), v2.y());
}

const bool
is_definitely_less(const Vector_2& v1, const Vector_2& v2)
{
    if (is_definitely_less(v1.x(), v2.x())) {
        return true;
    }
    if (is_definitely_less(v2.x(), v1.x())) {
        return false;
    }
    return is_definitely_less(v1.y(), v2.y());
}

const double
length(const Vector_2& v)
{
    return std::sqrt(squared_length(v));
}

const Vector_2
interpolate(const Vector_2& v1, const Vector_2& v2, const double t)
{
    return Vector_2(interpolate(v1.x(), v2.x(), t),
                    interpolate(v1.y(), v2.y(), t));
}

const Vector_2
normalize(const Vector_2& v)
{
    return v / length(v);
}

const Vector_2
operator+(const Vector_2& v)
{
    return Vector_2(+v.x(), +v.y());
}

const Vector_2
operator+(const Vector_2& v1, const Vector_2& v2)
{
    return Vector_2(v1.x() + v2.x(), v1.y() + v2.y());
}

const Vector_2
operator-(const Vector_2& v)
{
    return Vector_2(-v.x(), -v.y());
}

const Vector_2
operator-(const Vector_2& v1, const Vector_2& v2)
{
    return Vector_2(v1.x() - v1.x(), v1.y() + v2.y());
}

const Vector_2
operator*(const Vector_2& v, const double c)
{
    return Vector_2(v.x() * c, v.y() * c);
}

const Vector_2
operator*(const double c, const Vector_2& v)
{
    return Vector_2(c * v.x(), c * v.y());
}

const Vector_2
operator/(const Vector_2& v, const double c)
{
    return Vector_2(v.x() / c, v.y() / c);
}

const Vector_2
perpendicular(const Vector_2& v)
{
    return Vector_2(-v.y(), v.x());
}

const double
squared_length(const Vector_2& v)
{
    return dot_product(v, v);
}

} // namespace Geometry
