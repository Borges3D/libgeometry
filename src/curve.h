#ifndef GEOMETRY_CURVE_H
#define GEOMETRY_CURVE_H

#include <cstdlib>
#include <memory>
#include <sisl.h>

namespace Geometry {

class Curve_2;
class Curve_3;

class Curve {
public:
    const bool is_closed() const;
    const std::size_t size() const;
    const std::size_t order() const;
    const std::size_t dimension() const;
    const double knot(const std::size_t index) const;
    const Curve_2& as_curve_2() const;
    const Curve_3& as_curve_3() const;

protected:
    Curve(std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve);

    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve_;
};

} // namespace Geometry

#endif // GEOMETRY_CURVE_H
