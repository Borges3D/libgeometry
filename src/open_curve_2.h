#ifndef GEOMETRY_OPEN_CURVE_2_H
#define GEOMETRY_OPEN_CURVE_2_H

#include "curve_2.h"

namespace Geometry {

class Polyline_2;

class Open_curve_2 : public Curve_2 {
public:
    std::shared_ptr<const Polyline_2>
    to_polyline_2(const double tolerance = 1E-3) const;
};

std::vector<std::shared_ptr<const Closed_curve_2>>
offset(const Open_curve_2& c, const Offset_options& options);

} // namespace Geometry

#endif // GEOMETRY_OPEN_CURVE_2_H
