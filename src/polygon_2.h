#ifndef GEOMETRY_POLYGON_2_H
#define GEOMETRY_POLYGON_2_H

#include "clip_options.h"
#include "point_2.h"
#include "offset_options.h"
#include <memory>
#include <vector>

namespace Geometry {

class Simple_polygon;

class Polygon_2 {
public:
    static std::shared_ptr<const Polygon_2>
    create(const std::vector<Point_2> points);
    const std::size_t size() const;
    const Point_2& operator[](std::size_t index) const;
    const Simple_polygon& as_simple_polygon() const;

protected:
    explicit Polygon_2(const std::vector<Point_2> points);

    const std::vector<Point_2> points_;
};

const std::vector<std::shared_ptr<const Simple_polygon>>
clip(const std::vector<std::reference_wrapper<const Polygon_2>>& pss1,
     const std::vector<std::reference_wrapper<const Polygon_2>>& pss2,
     const Clip_options& options);
const double length(const Polygon_2& ps);
const std::vector<std::shared_ptr<const Polygon_2>>
offset(const Polygon_2& ps, const Offset_options& options);
const std::vector<double> parameters(const Polygon_2& ps);

} // namespace Geometry

#endif // GEOMETRY_POLYGON_2_H
