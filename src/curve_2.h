#ifndef GEOMETRY_CURVE_2_H
#define GEOMETRY_CURVE_2_H

#include "curve.h"
#include "offset_options.h"
#include "point_2.h"
#include <vector>

namespace Geometry {

class Closed_curve_2;
class Curve_3;
class Open_curve_2;

class Curve_2 : public Curve {
public:
    const Closed_curve_2& as_closed_curve_2() const;
    const Open_curve_2& as_open_curve_2() const;
    const Point_2 control(const std::size_t index) const;
    std::shared_ptr<const Curve_3> to_curve_3() const;

protected:
    Curve_2(Internal::Unique_sisl_curve_ptr curve);
};

std::vector<std::shared_ptr<const Curve_2>>
offset(const Curve_2& c, const Offset_options& options);

} // namespace Geometry

#endif // GEOMETRY_CURVE_2_H
