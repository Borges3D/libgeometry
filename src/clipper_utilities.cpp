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
    ps_.push_back(to_point_2(ps.front()));
    for (std::size_t index = 1; index < ps.size(); ++index) {
        const Point_2& p = to_point_2(ps[index]);
        if (is_approximately_equal(p, ps_.back())) {
            continue;
        }
        ps_.push_back(p);
    }
    return Polygon_2::create(std::move(ps_));
}

} // namespace Geometry
