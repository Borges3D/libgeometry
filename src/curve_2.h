#ifndef GEOMETRY_CURVE_2_H
#define GEOMETRY_CURVE_2_H

#include "curve.h"
#include "point_2.h"

namespace Geometry {

class Curve_2 : public Curve {
public:
    const Point_2 control(const std::size_t index) const;
};

} // namespace Geometry

#endif // GEOMETRY_CURVE_2_H
