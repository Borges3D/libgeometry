#ifndef GEOMETRY_POINT_2_H
#define GEOMETRY_POINT_2_H

#include "vector_2.h"

namespace Geometry {

class Point_2 {
public:
    Point_2(const double x, const double y);
    const double& x() const;
    const double& y() const;

private:
    const double x_;
    const double y_;
};

const double distance(const Point_2& p1, const Point_2& p2);
const bool is_approximately_equal(const Point_2& p1, const Point_2& p2);
const bool is_definitely_less(const Point_2& p1, const Point_2& p2);
const Point_2 operator+(const Point_2& p, const Vector_2& v);
const Point_2 operator-(const Point_2& p, const Vector_2& v);
const Vector_2 operator-(const Point_2& p1, const Point_2& p2);
const double squared_distance(const Point_2& p1, const Point_2& p2);

} // namespace Geometry

#endif // GEOMETRY_POINT_2_H
