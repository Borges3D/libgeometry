#include "circle_2.h"

namespace Geometry {

Circle_2::Circle_2(const Point_2& center, const double radius)
    : center_(center), radius_(radius)
{
}

const Point_2&
Circle_2::center() const
{
    return center_;
}

const double&
Circle_2::radius() const
{
    return radius_;
}

} // namespace Geometry
