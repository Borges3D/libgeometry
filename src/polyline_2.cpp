#include "polyline_2.h"
#include "clipper_utilities.h"
#include "utilities.h"
#include <cassert>
#include <utility>

namespace Geometry {

namespace {

ClipperLib::Path
to_path(const Polyline_2& polyline)
{
    ClipperLib::Path path;
    for (std::size_t index = 0; index < polyline.size(); ++index) {
        path.push_back(to_int_point(polyline.point(index)));
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
Polyline_2::point(std::size_t index) const
{
    return points_[index];
}

Polyline_2::Polyline_2(const std::vector<Point_2> points)
    : points_(std::move(points))
{
    assert(points_.size() >= 2);
}

std::vector<std::shared_ptr<const Polygon_2>>
offset(const Polyline_2& polyline, const Offset_options& options)
{
    ClipperLib::ClipperOffset offset;
    offset.AddPath(to_path(polyline), to_join_type(options.join_type),
                   to_end_type(options.cap_type));
    ClipperLib::Paths paths;
    offset.ArcTolerance = to_fixed(absolute_epsilon);
    offset.MiterLimit = options.miter_limit;
    offset.Execute(paths, to_fixed(options.distance));
    std::vector<std::shared_ptr<const Polygon_2>> polygons;
    for (const ClipperLib::Path& path : paths) {
        polygons.push_back(to_polygon_2(path));
    }
    return polygons;
}

} // namespace Geometry
