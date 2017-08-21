#ifndef GEOMETRY_CURVE_H
#define GEOMETRY_CURVE_H

#include <cstdlib>
#include <memory>
#include <sisl.h>

namespace Geometry {

class Circle_2;
class Curve_2;
class Closed_curve_2;
class Open_curve_2;
class Point_2;
class Polygon_2;
class Polyline_2;
class Rectangle_2;

class Curve {
public:
    static const std::shared_ptr<const Closed_curve_2>
    create(const Circle_2& c);
    static const std::shared_ptr<const Closed_curve_2>
    create(const Polygon_2& ps);
    static const std::shared_ptr<const Open_curve_2>
    create(const Polyline_2& ps);
    static const std::shared_ptr<const Closed_curve_2>
    create(const Rectangle_2& r);
    static const std::shared_ptr<const Closed_curve_2>
    fit_closed(const bool periodic, const std::size_t order,
               const std::vector<Point_2>& ps);
    static const std::shared_ptr<const Open_curve_2>
    fit_open(const std::size_t order, const std::vector<Point_2>& ps);
    const bool is_closed() const;
    const std::size_t size() const;
    const std::size_t order() const;
    const std::size_t dimension() const;
    const double knot(const std::size_t index) const;
    const Curve_2& as_curve_2() const;
    const Closed_curve_2& as_closed_curve_2() const;
    const Open_curve_2& as_open_curve_2() const;

protected:
    Curve(std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve);

    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve_;
};

} // namespace Geometry

#endif // GEOMETRY_CURVE_H
