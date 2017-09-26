#ifndef GEOMETRY_CLOSED_CURVE_2_H
#define GEOMETRY_CLOSED_CURVE_2_H

#include "curve_2.h"
#include "clip_options.h"

namespace Geometry {

class Circle;
class Polygon_2;
class Rectangle;

class Closed_curve_2 : public Curve_2 {
public:
    static std::shared_ptr<const Closed_curve_2>
    create(const Circle& c);
    static std::shared_ptr<const Closed_curve_2>
    create(const Polygon_2& ps);
    static std::shared_ptr<const Closed_curve_2>
    create(const Rectangle& r);
    static std::shared_ptr<const Closed_curve_2>
    fit(const std::size_t order, const Polygon_2& ps,
        const double smoothness = 0.5);
    static std::shared_ptr<const Closed_curve_2>
    fit(const bool is_periodic, const std::size_t order,
        const std::vector<Point_2>& ps);
    const bool is_periodic() const;
    std::shared_ptr<const Open_curve_2> split(const double u) const;

private:
    Closed_curve_2(Internal::Unique_sisl_curve_ptr curve);
};

std::vector<std::shared_ptr<const Closed_curve_2>>
clip(const std::vector<std::reference_wrapper<const Closed_curve_2>>& cs1, 
     const std::vector<std::reference_wrapper<const Closed_curve_2>>& cs2, 
     const Clip_options& options);
std::vector<std::shared_ptr<const Closed_curve_2>>
offset(const Closed_curve_2& c, const Offset_options& options);
std::shared_ptr<const Polygon_2>
linearize(const Closed_curve_2& c, const double tolerance = 1E-3);

} // namespace Geometry

#endif // GEOMETRY_CLOSED_CURVE_2_H
