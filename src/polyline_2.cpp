#include "polyline_2.h"
#include "clipper_utilities.h"
#include <cassert>
#include <utility>

namespace Geometry {

std::shared_ptr<const Polyline_2>
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

const double
length(const Polyline_2& ps)
{
    double len = 0.0;
    for (std::size_t index = 1; index < ps.size(); ++index) {
        len += distance(ps[index - 1], ps[index]);
    }
    return len;
}

const std::vector<std::shared_ptr<const Polygon_2>>
offset(const Polyline_2& ps, const Offset_options& options)
{
    ClipperLib::ClipperOffset offset;
    offset.AddPath(Internal::to_path(ps),
                   Internal::to_join_type(options.join_type),
                   Internal::to_end_type(options.cap_type));
    ClipperLib::Paths paths;
    offset.ArcTolerance = Internal::to_fixed(options.tolerance);
    offset.MiterLimit = options.miter_limit;
    offset.Execute(paths, Internal::to_fixed(options.distance));
    std::vector<std::shared_ptr<const Polygon_2>> pss;
    for (const ClipperLib::Path& path : paths) {
        pss.push_back(Internal::to_polygon_2(path));
    }
    return pss;
}

const std::vector<double>
parameters(const Polyline_2& ps)
{
    const double len = length(ps);
    std::vector<double> ts;
    ts.reserve(ps.size());
    double d = 0.0;
    ts.push_back(0.0);
    for (std::size_t index = 1; index < ps.size(); ++index) {
        d += distance(ps[index - 1], ps[index]);
        ts.push_back(d / len);
    }
    return ts;
}

} // namespace Geometry
