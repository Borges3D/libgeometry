#include "circle.h"

namespace Geometry {

Circle::Circle(const Point_2& center, const double radius)
    : center_(center), radius_(radius)
{
}

const Point_2&
Circle::center() const
{
    return center_;
}

const double&
Circle::radius() const
{
    return radius_;
}

} // namespace Geometry
