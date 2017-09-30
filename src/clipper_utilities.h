#ifndef GEOMETRY_CLIPPER_UTILITIES_H
#define GEOMETRY_CLIPPER_UTILITIES_H

#include "cap_type.h"
#include "clip_type.h"
#include "join_type.h"
#include "point_2.h"
#include <clipper.hpp>
#include <memory>

namespace Geometry {

class Polygon_2;
class Polyline_2;
class Simple_polygon;
class Simple_polygon_node;

namespace Internal {

const ClipperLib::ClipType to_clip_type(const Clip_type type);
const ClipperLib::EndType to_end_type(const Cap_type type);
const std::int64_t to_fixed(const double x);
const double to_float(const std::int64_t x);
ClipperLib::IntPoint to_int_point(const Point_2& p);
const ClipperLib::JoinType to_join_type(const Join_type type);
ClipperLib::Path to_path(const Polygon_2& ps);
ClipperLib::Path to_path(const Polyline_2& ps);
Point_2 to_point_2(const ClipperLib::IntPoint& p);
std::shared_ptr<const Polygon_2>
to_polygon_2(const ClipperLib::Path& path);
std::shared_ptr<const Simple_polygon>
to_simple_polygon(const ClipperLib::Path& path);
std::unique_ptr<const Simple_polygon_node>
to_simple_polygon_tree(const ClipperLib::PolyTree& tree);

} // namespace Internal

} // namespace Geometry

#endif // GEOMETRY_CLIPPER_UTILITIES_H
