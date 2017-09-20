#ifndef GEOMETRY_CURVE_H
#define GEOMETRY_CURVE_H

#include "unique_sisl_curve_ptr.h"

namespace Geometry {

class Curve_2;
class Curve_3;

class Curve {
public:
    const Curve_2& as_curve_2() const;
    const Curve_3& as_curve_3() const;
    const std::size_t dimension() const;
    const bool is_closed() const;
    const double knot(const std::size_t index) const;
    const std::size_t order() const;
    const std::size_t size() const;
    const double u_min() const;
    const double u_max() const;

protected:
    Curve(Internal::Unique_sisl_curve_ptr curve);

    Internal::Unique_sisl_curve_ptr curve_;
};

} // namespace Geometry

#endif // GEOMETRY_CURVE_H
