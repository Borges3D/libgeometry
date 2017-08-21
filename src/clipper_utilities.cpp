#include "clipper_utilities.h"
#include "utilities.h"
#include "polygon_2.h"
#include <cmath>

namespace Geometry {

ClipperLib::IntPoint
to_int_point(const Point_2& p)
{
    return ClipperLib::IntPoint(to_fixed(p.x()), to_fixed(p.y()));
}

Point_2
to_point_2(const ClipperLib::IntPoint& p)
{
    return Point_2(to_float(p.X), to_float(p.Y));
}

const std::shared_ptr<const Polygon_2>
to_polygon_2(const ClipperLib::Path& ps)
{
    std::vector<Point_2> ps_;
    for (const ClipperLib::IntPoint& p : ps) {
        ps_.push_back(to_point_2(p));
    }
    return Polygon_2::create(std::move(ps_));
}

} // namespace Geometry
