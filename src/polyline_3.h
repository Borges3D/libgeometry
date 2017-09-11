#ifndef GEOMETRY_POLYLINE_3_H
#define GEOMETRY_POLYLINE_3_H

#include "point_3.h"
#include <vector>

namespace Geometry {

class Polyline_3 {
public:
    static std::shared_ptr<const Polyline_3>
    create(const std::vector<Point_3> points);
    const std::size_t size() const;
    const Point_3& operator[](std::size_t index) const;

private:
    explicit Polyline_3(const std::vector<Point_3> points);

    const std::vector<Point_3> points_;
};

const double length(const Polyline_3& ps);
const std::vector<double> parameters(const Polyline_3& ps);

} // namespace Geometry

#endif // GEOMETRY_POLYLINE_3_H
