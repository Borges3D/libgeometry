#ifndef GEOMETRY_POINT_3_H
#define GEOMETRY_POINT_3_H

#include "vector_3.h"

namespace Geometry {

class Point_3 {
public:
    Point_3(const double x, const double y, const double z);
    const double& x() const;
    const double& y() const;
    const double& z() const;

private:
    const double x_;
    const double y_;
    const double z_;
};

const double distance(const Point_3& p1, const Point_3& p2);
const bool is_approximately_equal(const Point_3& p1, const Point_3& p2);
const bool is_definitely_less(const Point_3& p1, const Point_3& p2);
const Point_3 operator+(const Point_3& p, const Vector_3& v);
const Point_3 operator-(const Point_3& p, const Vector_3& v);
const Vector_3 operator-(const Point_3& p1, const Point_3& p2);
const double squared_distance(const Point_3& p1, const Point_3& p2);

} // namespace Geometry

#endif // GEOMETRY_POINT_3_H
