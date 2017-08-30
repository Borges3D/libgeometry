#ifndef GEOMETRY_CLIPPER_UTILITIES_H
#define GEOMETRY_CLIPPER_UTILITIES_H

#include <clipper.hpp>
#include <memory>
#include "offset_options.h"

namespace Geometry {

class Point_2;
class Polygon_2;

const ClipperLib::EndType to_end_type(const Cap_type type);
const ClipperLib::JoinType to_join_type(const Join_type type);
ClipperLib::IntPoint to_int_point(const Point_2& p);
Point_2 to_point_2(const ClipperLib::IntPoint& p);
const std::shared_ptr<const Polygon_2>
to_polygon_2(const ClipperLib::Path& path);

} // namespace Geometry

#endif // GEOMETRY_CLIPPER_UTILITIES_H
