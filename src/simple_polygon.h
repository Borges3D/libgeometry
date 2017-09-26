#ifndef GEOMETRY_SIMPLE_POLYGON_2_H
#define GEOMETRY_SIMPLE_POLYGON_2_H

#include "polygon_2.h"

namespace Geometry {

class Mesh_2;

class Simple_polygon : public Polygon_2 {
public:
    static std::shared_ptr<const Simple_polygon>
    create(const std::vector<Point_2> points);

private:
    explicit Simple_polygon(const std::vector<Point_2> points);
};

std::vector<std::shared_ptr<const Simple_polygon>>
simplify(const Polygon_2& ps);
std::shared_ptr<const Mesh_2> triangulate(const Simple_polygon& ps);

} // namespace Geometry

#endif // GEOMETRY_SIMPLE_POLYGON_2_H
