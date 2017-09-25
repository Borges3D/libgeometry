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
    std::tuple<std::shared_ptr<const Open_curve_2>,
               std::shared_ptr<const Open_curve_2>>
    split(const double u) const;

private:
    friend class Closed_curve_2;
    friend class Curve_2;

    Open_curve_2(Internal::Unique_sisl_curve_ptr curve);
};

std::vector<std::shared_ptr<const Closed_curve_2>>
offset(const Open_curve_2& c, const Offset_options& options);
std::shared_ptr<const Polyline_2>
to_polyline_2(const Open_curve_2& c, const double tolerance = 1E-3);

} // namespace Geometry

#endif // GEOMETRY_OPEN_CURVE_2_H
