#include "polygon_2.h"
#include "clipper_utilities.h"
#include <cassert>
#include <utility>

namespace Geometry {

std::shared_ptr<const Polygon_2>
Polygon_2::create(const std::vector<Point_2> points)
{
    return std::shared_ptr<const Polygon_2>(new Polygon_2(std::move(points)));
}

const std::size_t
Polygon_2::size() const
{
    return points_.size();
}

const Point_2&
Polygon_2::operator[](std::size_t index) const
{
    assert(index < points_.size());
    return points_[index];
}

Polygon_2::Polygon_2(const std::vector<Point_2> points)
    : points_(std::move(points))
{
    assert(points_.size() >= 3);
#ifndef NDEBUG
    for (std::size_t index = 0; index < points.size() - 1; ++index) {
        assert(!is_approximately_equal(points_[index], points[index + 1]));
    }
#endif // !NDEBUG
    assert(!is_approximately_equal(points_.back(), points_.front()));
}

const std::vector<std::shared_ptr<const Polygon_2>>
clip(const Clip_type type,
     const std::vector<std::reference_wrapper<const Polygon_2>>& pss1,
     const std::vector<std::reference_wrapper<const Polygon_2>>& pss2)
{
    ClipperLib::Clipper clipper;
    for (const Polygon_2& ps : pss1) {
        clipper.AddPath(Internal::to_path(ps), ClipperLib::ptSubject, true);
    }
    for (const Polygon_2& ps : pss2) {
        clipper.AddPath(Internal::to_path(ps), ClipperLib::ptClip, true);
    }
    ClipperLib::Paths pss_;
    clipper.Execute(Internal::to_clip_type(type), pss_, ClipperLib::pftNonZero,
                    ClipperLib::pftNonZero);
    std::vector<std::shared_ptr<const Polygon_2>> pss;
    for (const ClipperLib::Path& ps : pss_) {
        pss.push_back(Internal::to_polygon_2(ps));
    }
    return pss;
}

const double
length(const Polygon_2& ps)
{
    double len = 0.0;
    for (std::size_t index = 1; index < ps.size(); ++index) {
        len += distance(ps[index - 1], ps[index]);
    }
    len += distance(ps[ps.size() - 1], ps[0]);
    return len;
}

const std::vector<std::shared_ptr<const Polygon_2>>
offset(const Polygon_2& ps, const Offset_options& options)
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
parameters(const Polygon_2& ps)
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
