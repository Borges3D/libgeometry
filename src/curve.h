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
class Polygon_2;
class Polyline_2;
class Rectangle_2;

class Curve {
public:
    static const std::shared_ptr<const Closed_curve_2>
    create(const Circle_2& circle);
    static const std::shared_ptr<const Closed_curve_2>
    create(const Polygon_2& polygon);
    static const std::shared_ptr<const Open_curve_2>
    create(const Polyline_2& polyline);
    static const std::shared_ptr<const Closed_curve_2>
    create(const Rectangle_2& rectangle);
    const bool is_closed() const;
    const std::size_t dimension() const;
    const Curve_2& as_curve_2() const;
    const Closed_curve_2& as_closed_curve_2() const;
    const Open_curve_2& as_open_curve_2() const;

protected:
    Curve(std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve);

    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve_;
};

} // namespace Geometry

#endif // GEOMETRY_CURVE_H
