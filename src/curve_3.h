#ifndef GEOMETRY_CURVE_3_H
#define GEOMETRY_CURVE_3_H

#include "curve.h"
#include "point_3.h"

namespace Geometry {

class Closed_curve_3;
class Open_curve_3;

class Curve_3 : public Curve {
public:
    const Point_3 control(const std::size_t index) const;
    const Closed_curve_3& as_closed_curve_3() const;
    const Open_curve_3& as_open_curve_3() const;

protected:
    friend class Curve_2;

    Curve_3(std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve);
};

} // namespace Geometry

#endif // GEOMETRY_CURVE_3_H
