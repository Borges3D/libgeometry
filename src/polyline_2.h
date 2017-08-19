#ifndef GEOMETRY_POLYLINE_2_H
#define GEOMETRY_POLYLINE_2_H

#include "point_2.h"
#include <memory>
#include <vector>

namespace Geometry {

class Polygon_2;

enum class Cap_type {
    Round,
    Square,
    Butt
};

enum class Join_type {
    Round,
    Miter,
    Square
};

struct Offset_options {
    Offset_options(double distance);

    Cap_type cap_type = Cap_type::Round;
    Join_type join_type = Join_type::Round;
    double miter_limit = 2.0;
    double distance;
};

class Polyline_2 {
public:
    static const std::shared_ptr<const Polyline_2>
    create(const std::vector<Point_2> points);
    const std::size_t size() const;
    const Point_2& point(std::size_t index) const;

private:
    explicit Polyline_2(const std::vector<Point_2> points);

    const std::vector<Point_2> points_;
};

std::vector<std::shared_ptr<const Polygon_2>>
offset(const Polyline_2& polyline, const Offset_options& options);

} // namespace Geometry

#endif // GEOMETRY_POLYLINE_2_H
