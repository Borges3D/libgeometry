#include "rectangle_2.h"

namespace Geometry {

Rectangle_2::Rectangle_2(const Point_2& start, const Point_2& end)
    : start_(start), end_(end)
{
}

const Point_2&
Rectangle_2::start() const
{
    return start_;
}

const Point_2&
Rectangle_2::end() const
{
    return end_;
}

} // namespace Geometry
