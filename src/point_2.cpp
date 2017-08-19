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

} // namespace Geometry
