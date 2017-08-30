#include "clipper_utilities.h"
#include "utilities.h"
#include "polygon_2.h"
#include <cmath>

namespace Geometry {

const ClipperLib::EndType
to_end_type(const Cap_type type)
{
    switch (type) {
    case Cap_type::butt:
        return ClipperLib::etOpenButt;
    case Cap_type::round:
        return ClipperLib::etOpenRound;
    case Cap_type::square:
        return ClipperLib::etOpenSquare;
    }
}

const ClipperLib::JoinType
to_join_type(const Join_type type)
{
    switch (type) {
    case Join_type::miter:
        return ClipperLib::jtMiter;
    case Join_type::round:
        return ClipperLib::jtRound;
    case Join_type::square:
        return ClipperLib::jtSquare;
    }
}

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
    for (std::size_t index = 1; index < ps.size() - 1; ++index) {
        const Point_2& p = to_point_2(ps[index]);
        if (!is_approximately_equal(p, ps_.back())) {
            ps_.push_back(p);
        }
    }
    const Point_2& p = to_point_2(ps.back());
    if (!is_approximately_equal(p, ps_.front())) {
        ps_.push_back(p);
    }
    return Polygon_2::create(std::move(ps_));
}

} // namespace Geometry
