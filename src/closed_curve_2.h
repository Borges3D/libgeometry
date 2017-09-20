#ifndef GEOMETRY_CLOSED_CURVE_2_H
#define GEOMETRY_CLOSED_CURVE_2_H

#include "curve_2.h"

namespace Geometry {

class Circle_2;
class Polygon_2;
class Rectangle_2;

class Closed_curve_2 : public Curve_2 {
public:
    static std::shared_ptr<const Closed_curve_2>
    create(const Circle_2& c);
    static std::shared_ptr<const Closed_curve_2>
    create(const Polygon_2& ps);
    static std::shared_ptr<const Closed_curve_2>
    create(const Rectangle_2& r);
    static std::shared_ptr<const Closed_curve_2>
    fit(const std::size_t order, const Polygon_2& ps,
        const double smoothness = 0.5);
    static std::shared_ptr<const Closed_curve_2>
    fit(const bool is_periodic, const std::size_t order,
        const std::vector<Point_2>& ps);
    const bool is_periodic() const;
    std::shared_ptr<const Open_curve_2> split(const double u) const;
    std::shared_ptr<const Polygon_2>
    to_polygon_2(const double tolerance = 1E-3) const;

private:
    Closed_curve_2(Internal::Unique_sisl_curve_ptr curve);
};

std::vector<std::shared_ptr<const Closed_curve_2>>
offset(const Closed_curve_2& c, const Offset_options& options);

} // namespace Geometry

#endif // GEOMETRY_CLOSED_CURVE_2_H
