#ifndef GEOMETRY_OPEN_CURVE_2_H
#define GEOMETRY_OPEN_CURVE_2_H

#include "curve_2.h"

namespace Geometry {

class Polyline_2;

class Open_curve_2 : public Curve_2 {
public:
    const std::shared_ptr<const Polyline_2>
    to_polyline_2(const double epsilon) const;
};

} // namespace Geometry

#endif // GEOMETRY_OPEN_CURVE_2_H
