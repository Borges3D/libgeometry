#ifndef GEOMETRY_POLYGON_2_H
#define GEOMETRY_POLYGON_2_H

#include "point_2.h"
#include <memory>
#include <vector>

namespace Geometry {

enum class Clip_type {
    Difference,
    Intersection,
    Union
};

class Polygon_2 {
public:
    static const std::shared_ptr<const Polygon_2>
    create(const std::vector<Point_2> points);
    const std::size_t size() const;
    const Point_2& point(std::size_t index) const;

private:
    explicit Polygon_2(const std::vector<Point_2> points);

    const std::vector<Point_2> points_;
};

std::vector<std::shared_ptr<const Polygon_2>>
clip(const Clip_type type,
     const std::vector<std::reference_wrapper<const Polygon_2>>& polygons_1,
     const std::vector<std::reference_wrapper<const Polygon_2>>& polygons_2);

} // namespace Geometry

#endif // GEOMETRY_POLYGON_2_H
