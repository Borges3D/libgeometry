#ifndef GEOMETRY_POLYLINE_2_H
#define GEOMETRY_POLYLINE_2_H

#include "point_2.h"
#include "offset_options.h"
#include <memory>
#include <vector>

namespace Geometry {

class Polygon_2;

class Polyline_2 {
public:
    static std::shared_ptr<const Polyline_2>
    create(const std::vector<Point_2> points);
    const std::size_t size() const;
    const Point_2& operator[](std::size_t index) const;

private:
    explicit Polyline_2(const std::vector<Point_2> points);

    const std::vector<Point_2> points_;
};

const std::vector<std::shared_ptr<const Polygon_2>>
offset(const Polyline_2& ps, const Offset_options& options);
const std::vector<double> parameters(const Polyline_2& ps);

} // namespace Geometry

#endif // GEOMETRY_POLYLINE_2_H
