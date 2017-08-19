#include "clipper_utilities.h"
#include "utilities.h"
#include "polygon_2.h"
#include <cmath>

namespace Geometry {

ClipperLib::IntPoint
to_int_point(const Point_2& point)
{
    return ClipperLib::IntPoint(to_fixed(point.x()), to_fixed(point.y()));
}

Point_2
to_point_2(const ClipperLib::IntPoint& point)
{
    return Point_2(to_float(point.X), to_float(point.Y));
}

const std::shared_ptr<const Polygon_2>
to_polygon_2(const ClipperLib::Path& path)
{
    std::vector<Point_2> points;
    for (const ClipperLib::IntPoint& point : path) {
        points.push_back(to_point_2(point));
    }
    return Polygon_2::create(std::move(points));
}

} // namespace Geometry
