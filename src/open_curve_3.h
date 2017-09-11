#ifndef GEOMETRY_OPEN_CURVE_3_H
#define GEOMETRY_OPEN_CURVE_3_H

#include "curve_3.h"

namespace Geometry {

class Polyline_3;

class Open_curve_3 : public Curve_3 {
public:
    static std::shared_ptr<const Open_curve_3>
    create(const Polyline_3& ps);
    static std::shared_ptr<const Open_curve_3>
    fit(const std::size_t order, const std::vector<Point_3>& ps);
    static std::shared_ptr<const Open_curve_3>
    fit(const std::size_t order, const Polyline_3& ps, const double smoothness);
    std::shared_ptr<const Polyline_3>
    to_polyline_3(const double tolerance = 1E-3) const;

private:
    Open_curve_3(std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve);
};

} // namespace Geometry

#endif // GEOMETRY_OPEN_CURVE_3_H
