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

std::shared_ptr<const Polygon_2>
to_polygon_2(const Rectangle_2& r)
{
    const Point_2& start = r.start();
    const double x1 = start.x();
    const double y1 = start.y();
    const Point_2& end = r.end();
    const double x2 = end.x();
    const double y2 = end.y();
    return Polygon_2::create(
        {Point_2(x1, y1), Point_2(x2, y1), Point_2(x2, y2), Point_2(x1, y2)});
}

} // namespace Geometry
