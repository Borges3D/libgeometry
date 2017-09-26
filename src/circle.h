#ifndef GEOMETRY_CIRCLE_H
#define GEOMETRY_CIRCLE_H

#include "point_2.h"

namespace Geometry {

class Circle {
public:
    Circle(const Point_2& center, const double radius);
    const Point_2& center() const;
    const double& radius() const;

private:
    const Point_2 center_;
    const double radius_;
};

} // namespace Geometry

#endif // GEOMETRY_CIRCLE_H
