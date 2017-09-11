#ifndef GEOMETRY_OPEN_CURVE_2_H
#define GEOMETRY_OPEN_CURVE_2_H

#include "curve_2.h"

namespace Geometry {

class Polyline_2;

class Open_curve_2 : public Curve_2 {
public:
    static std::shared_ptr<const Open_curve_2>
    create(const Polyline_2& ps);
    static std::shared_ptr<const Open_curve_2>
    fit(const std::size_t order, const std::vector<Point_2>& ps);
    static std::shared_ptr<const Open_curve_2>
    fit(const std::size_t order, const Polyline_2& ps, const double smoothness);
    std::shared_ptr<const Polyline_2>
    to_polyline_2(const double tolerance = 1E-3) const;

private:
    Open_curve_2(std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve);
};

std::vector<std::shared_ptr<const Closed_curve_2>>
offset(const Open_curve_2& c, const Offset_options& options);

} // namespace Geometry

#endif // GEOMETRY_OPEN_CURVE_2_H
