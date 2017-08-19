#ifndef GEOMETRY_RECTANGLE_2_H
#define GEOMETRY_RECTANGLE_2_H

#include "point_2.h"

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

} // namespace Geometry

#endif // GEOMETRY_RECTANGLE_2_H
