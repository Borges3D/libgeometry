#include "polygon_2.h"
#include "clipper_utilities.h"
#include <cassert>
#include <utility>

namespace Geometry {

namespace {

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

} // namespace

const std::shared_ptr<const Polygon_2>
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
    assert(!is_approximately_equal(points_[points.size() - 1], points[0]));
}

const std::vector<std::shared_ptr<const Polygon_2>>
clip(const Clip_type type,
     const std::vector<std::reference_wrapper<const Polygon_2>>& pss1,
     const std::vector<std::reference_wrapper<const Polygon_2>>& pss2)
{
    ClipperLib::Clipper clipper;
    for (const Polygon_2& ps : pss1) {
        clipper.AddPath(to_path(ps), ClipperLib::ptSubject, true);
    }
    for (const Polygon_2& ps : pss2) {
        clipper.AddPath(to_path(ps), ClipperLib::ptClip, true);
    }
    ClipperLib::Paths pss_;
    clipper.Execute(to_clip_type(type), pss_, ClipperLib::pftNonZero,
                    ClipperLib::pftNonZero);
    std::vector<std::shared_ptr<const Polygon_2>> pss;
    for (const ClipperLib::Path& ps : pss_) {
        pss.push_back(to_polygon_2(ps));
    }
    return pss;
}

const std::vector<double>
parameters(const Polygon_2& ps)
{
    std::vector<double> ts;
    ts.reserve(ps.size());
    double dsum = 0.0;
    ts.push_back(dsum);
    for (std::size_t index = 1; index < ps.size(); ++index) {
        dsum += distance(ps[index - 1], ps[index]);
        ts.push_back(dsum);
    }
    dsum += distance(ps[ps.size() - 1], ps[0]);
    for (double& t : ts) {
        t /= dsum;
    }
    return ts;
}

} // namespace Geometry
