#include "rectangle.h"
#include "simple_polygon.h"

namespace Geometry {

Rectangle::Rectangle(const Point_2& position, const Vector_2& size)
    : position_(position), size_(size)
{
}

const Point_2&
Rectangle::position() const
{
    return position_;
}

const Vector_2&
Rectangle::size() const
{
    return size_;
}

std::shared_ptr<const Simple_polygon>
to_simple_polygon(const Rectangle& r)
{
    const Point_2& position = r.position();
    const Vector_2& size = r.size();
    const double x1 = position.x();
    const double y1 = position.y();
    const double x2 = x1 + size.x();
    const double y2 = y1 + size.y();
    return Simple_polygon::create(
        {Point_2(x1, y1), Point_2(x2, y1), Point_2(x2, y2), Point_2(x1, y2)});
}

} // namespace Geometry
