#ifndef GEOMETRY_CLOSED_CURVE_3_H
#define GEOMETRY_CLOSED_CURVE_3_H

#include "curve_3.h"

namespace Geometry {

class Polygon_3;

class Closed_curve_3 : public Curve_3 {
public:
    static std::shared_ptr<const Closed_curve_3>
    create(const Polygon_3& ps);
    static std::shared_ptr<const Closed_curve_3>
    fit(const std::size_t order, const Polygon_3& ps,
        const double smoothness = 0.5);
    static std::shared_ptr<const Closed_curve_3>
    fit(const bool is_periodic, const std::size_t order,
        const std::vector<Point_3>& ps);
    std::shared_ptr<const Open_curve_3> split(const double u) const;

private:
    Closed_curve_3(Internal::Unique_sisl_curve_ptr curve);
};

std::shared_ptr<const Polygon_3>
to_polygon_3(const Closed_curve_3& c, const double tolerance = 1E-3);

} // namespace Geometry

#endif // GEOMETRY_CLOSED_CURVE_3_H
