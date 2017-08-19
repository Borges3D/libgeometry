#ifndef GEOMETRY_CLIPPER_UTILITIES_H
#define GEOMETRY_CLIPPER_UTILITIES_H

#include <clipper.hpp>
#include <memory>

namespace Geometry {

class Point_2;
class Polygon_2;

ClipperLib::IntPoint to_int_point(const Point_2& point);
Point_2 to_point_2(const ClipperLib::IntPoint& point);
const std::shared_ptr<const Polygon_2>
to_polygon_2(const ClipperLib::Path& path);

} // namespace Geometry

#endif // GEOMETRY_CLIPPER_UTILITIES_H
