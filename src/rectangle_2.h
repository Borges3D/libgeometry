#ifndef GEOMETRY_RECTANGLE_2_H
#define GEOMETRY_RECTANGLE_2_H

#include "polygon_2.h"

namespace Geometry {

class Rectangle_2 {
public:
    Rectangle_2(const Point_2& start, const Point_2& end);
    const Point_2& start() const;
    const Point_2& end() const;

private:
    const Point_2 start_;
    const Point_2 end_;
};

std::shared_ptr<const Polygon_2> to_polygon_2(const Rectangle_2& r);

} // namespace Geometry

#endif // GEOMETRY_RECTANGLE_2_H
