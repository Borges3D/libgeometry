#ifndef GEOMETRY_CLOSED_CURVE_2_H
#define GEOMETRY_CLOSED_CURVE_2_H

#include "curve_2.h"

namespace Geometry {

class Polygon_2;

class Closed_curve_2 : public Curve_2 {
public:
    const std::shared_ptr<const Polygon_2>
    to_polygon_2(const double epsilon) const;
};

} // namespace Geometry

#endif // GEOMETRY_CLOSED_CURVE_2_H
