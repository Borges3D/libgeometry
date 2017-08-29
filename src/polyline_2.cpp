#include "polyline_2.h"
#include "clipper_utilities.h"
#include "utilities.h"
#include <cassert>
#include <utility>

namespace Geometry {

namespace {

ClipperLib::Path
to_path(const Polyline_2& ps)
{
    ClipperLib::Path path;
    for (std::size_t index = 0; index < ps.size(); ++index) {
        path.push_back(to_int_point(ps[index]));
    }
    return path;
}

const ClipperLib::EndType
to_end_type(const Cap_type type)
{
    switch (type) {
    case Cap_type::Butt:
        return ClipperLib::etOpenButt;
    case Cap_type::Round:
        return ClipperLib::etOpenRound;
    case Cap_type::Square:
        return ClipperLib::etOpenSquare;
    }
}

const ClipperLib::JoinType
to_join_type(const Join_type type)
{
    switch (type) {
    case Join_type::Miter:
        return ClipperLib::jtMiter;
    case Join_type::Round:
        return ClipperLib::jtRound;
    case Join_type::Square:
        return ClipperLib::jtSquare;
    }
}

} // namespace

Offset_options::Offset_options(double distance) : distance(distance)
{
}

const std::shared_ptr<const Polyline_2>
Polyline_2::create(const std::vector<Point_2> points)
{
    return std::shared_ptr<const Polyline_2>(new Polyline_2(std::move(points)));
}

const std::size_t
Polyline_2::size() const
{
    return points_.size();
}

const Point_2&
Polyline_2::operator[](std::size_t index) const
{
    assert(index < points_.size());
    return points_[index];
}

Polyline_2::Polyline_2(const std::vector<Point_2> points)
    : points_(std::move(points))
{
    assert(points_.size() >= 2);
#ifndef NDEBUG
    for (std::size_t index = 0; index < points.size() - 1; ++index) {
        assert(!is_approximately_equal(points_[index], points[index + 1]));
    }
#endif // !NDEBUG
}

const std::vector<std::shared_ptr<const Polygon_2>>
offset(const Polyline_2& ps, const Offset_options& options)
{
    ClipperLib::ClipperOffset offset;
    offset.AddPath(to_path(ps), to_join_type(options.join_type),
                   to_end_type(options.cap_type));
    ClipperLib::Paths paths;
    offset.ArcTolerance = to_fixed(absolute_epsilon);
    offset.MiterLimit = options.miter_limit;
    offset.Execute(paths, to_fixed(options.distance));
    std::vector<std::shared_ptr<const Polygon_2>> pss;
    for (const ClipperLib::Path& path : paths) {
        pss.push_back(to_polygon_2(path));
    }
    return pss;
}

const std::vector<double>
parameters(const Polyline_2& ps)
{
    std::vector<double> ts;
    ts.reserve(ps.size());
    double dsum = 0.0;
    ts.push_back(dsum);
    for (std::size_t index = 1; index < ps.size(); ++index) {
        dsum += distance(ps[index - 1], ps[index]);
        ts.push_back(dsum);
    }
    for (double& t : ts) {
        t /= dsum;
    }
    return ts;
}

} // namespace Geometry
