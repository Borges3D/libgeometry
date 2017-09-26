#include "clipper_utilities.h"
#include "polyline_2.h"
#include "simple_polygon.h"
#include <cmath>
#include <utility>

namespace Geometry {

namespace Internal {

namespace {

constexpr int fractional_bits = 32;

} // namespace

const ClipperLib::ClipType
to_clip_type(const Clip_type type)
{
    switch (type) {
    case Clip_type::Difference:
        return ClipperLib::ctDifference;
    case Clip_type::Intersection:
        return ClipperLib::ctIntersection;
    case Clip_type::Union:
        return ClipperLib::ctUnion;
    }
}

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

const std::int64_t
to_fixed(const double x)
{
    return std::round(x * (1ull << fractional_bits));
}

const double
to_float(const std::int64_t x)
{
    return static_cast<double>(x) / (1ull << fractional_bits);
}

ClipperLib::IntPoint
to_int_point(const Point_2& p)
{
    return ClipperLib::IntPoint(to_fixed(p.x()), to_fixed(p.y()));
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

ClipperLib::Path
to_path(const Polygon_2& ps)
{
    ClipperLib::Path path;
    for (std::size_t index = 0; index < ps.size(); ++index) {
        path.push_back(to_int_point(ps[index]));
    }
    path.push_back(to_int_point(ps[0]));
    return path;
}

ClipperLib::Path
to_path(const Polyline_2& ps)
{
    ClipperLib::Path path;
    for (std::size_t index = 0; index < ps.size(); ++index) {
        path.push_back(to_int_point(ps[index]));
    }
    return path;
}

Point_2
to_point_2(const ClipperLib::IntPoint& p)
{
    return Point_2(to_float(p.X), to_float(p.Y));
}

std::shared_ptr<const Polygon_2>
to_polygon_2(const ClipperLib::Path& ps)
{
    if (ps.empty()) {
        return nullptr;
    }
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

std::shared_ptr<const Simple_polygon>
to_simple_polygon(const ClipperLib::Path& ps)
{
    if (ps.empty()) {
        return nullptr;
    }
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
    return Simple_polygon::create(std::move(ps_));
}

} // namespace Internal

} // namespace Geometry
