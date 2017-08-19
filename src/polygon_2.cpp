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
to_path(const Polygon_2& polygon)
{
    ClipperLib::Path path;
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        path.push_back(to_int_point(polygon.point(index)));
    }
    path.push_back(to_int_point(polygon.point(0)));
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
Polygon_2::point(std::size_t index) const
{
    return points_[index];
}

Polygon_2::Polygon_2(const std::vector<Point_2> points)
    : points_(std::move(points))
{
    assert(points_.size() >= 3);
}

std::vector<std::shared_ptr<const Polygon_2>>
clip(const Clip_type type,
     const std::vector<std::reference_wrapper<const Polygon_2>>& polygons_1,
     const std::vector<std::reference_wrapper<const Polygon_2>>& polygons_2)
{
    ClipperLib::Clipper clipper;
    for (const Polygon_2& polygon : polygons_1) {
        clipper.AddPath(to_path(polygon), ClipperLib::ptSubject, true);
    }
    for (const Polygon_2& polygon : polygons_2) {
        clipper.AddPath(to_path(polygon), ClipperLib::ptClip, true);
    }
    ClipperLib::Paths paths;
    clipper.Execute(to_clip_type(type), paths, ClipperLib::pftNonZero,
                    ClipperLib::pftNonZero);
    std::vector<std::shared_ptr<const Polygon_2>> polygons;
    for (const ClipperLib::Path& path : paths) {
        polygons.push_back(to_polygon_2(path));
    }
    return polygons;
}

} // namespace Geometry
