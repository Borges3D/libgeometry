#include "vector_2.h"
#include "point_2.h"
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
dot_product(const Vector_2& v1, const Vector_2& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}

const double
length(const Vector_2& v)
{
    return std::sqrt(squared_length(v));
}

const double
squared_length(const Vector_2& v)
{
    return dot_product(v, v);
}

} // namespace Geometry
