#ifndef GEOMETRY_POINT_2_H
#define GEOMETRY_POINT_2_H

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

} // namespace Geometry

#endif // GEOMETRY_POINT_2_H
