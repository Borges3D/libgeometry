#include "vector_3.h"
#include "scalar.h"
#include <cmath>

namespace Geometry {

Vector_3::Vector_3(const double x, const double y, const double z)
    : x_(x), y_(y), z_(z)
{
}

const double&
Vector_3::x() const
{
    return x_;
}

const double&
Vector_3::y() const
{
    return y_;
}

const double&
Vector_3::z() const
{
    return z_;
}

const Vector_3
cross_product(const Vector_3& v1, const Vector_3& v2)
{
    const double x1 = v1.x();
    const double y1 = v1.y();
    const double z1 = v1.z();
    const double x2 = v2.x();
    const double y2 = v2.y();
    const double z2 = v2.z();
    return Vector_3(y1 * z2 - z1 * y2, z1 * y2 - y1 * z2, x1 * y2 - y1 * x2);
}

const double
dot_product(const Vector_3& v1, const Vector_3& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

const bool
is_approximately_equal(const Vector_3& v1, const Vector_3& v2)
{
    if (!is_approximately_equal(v1.x(), v2.x())) {
        return false;
    }
    if (!is_approximately_equal(v1.y(), v2.y())) {
        return false;
    }
    return is_approximately_equal(v1.z(), v2.z());
}

const bool
is_definitely_less(const Vector_3& v1, const Vector_3& v2)
{
    if (is_definitely_less(v1.x(), v2.x())) {
        return true;
    }
    if (is_definitely_less(v2.x(), v1.x())) {
        return false;
    }
    if (is_definitely_less(v1.y(), v2.y())) {
        return true;
    }
    if (is_definitely_less(v2.y(), v1.y())) {
        return false;
    }
    return is_definitely_less(v1.z(), v2.z());
}

const double
length(const Vector_3& v)
{
    return std::sqrt(squared_length(v));
}

const Vector_3
interpolate(const Vector_3& v1, const Vector_3& v2, const double t)
{
    return Vector_3(interpolate(v1.x(), v2.x(), t),
                    interpolate(v1.y(), v2.y(), t),
                    interpolate(v1.z(), v2.z(), t));
}

const Vector_3
normalize(const Vector_3& v)
{
    return v / length(v);
}

const Vector_3
operator+(const Vector_3& v)
{
    return Vector_3(+v.x(), +v.y(), +v.z());
}

const Vector_3
operator+(const Vector_3& v1, const Vector_3& v2)
{
    return Vector_3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

const Vector_3
operator-(const Vector_3& v)
{
    return Vector_3(-v.x(), -v.y(), -v.z());
}

const Vector_3
operator-(const Vector_3& v1, const Vector_3& v2)
{
    return Vector_3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

const Vector_3
operator*(const Vector_3& v, const double c)
{
    return Vector_3(v.x() * c, v.y() * c, v.z() * c);
}

const Vector_3
operator*(const double c, const Vector_3& v)
{
    return Vector_3(c * v.x(), c * v.y(), c * v.z());
}

const Vector_3
operator/(const Vector_3& v, const double c)
{
    return Vector_3(v.x() / c, v.y() / c, v.z() / c);
}

const double
squared_length(const Vector_3& v)
{
    return dot_product(v, v);
}

} // namespace Geometry
