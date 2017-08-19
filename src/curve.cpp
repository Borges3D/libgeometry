#include "curve.h"
#include "circle_2.h"
#include "closed_curve_2.h"
#include "curve_2.h"
#include "open_curve_2.h"
#include "polygon_2.h"
#include "polyline_2.h"
#include "rectangle_2.h"
#include <cassert>
#include <utility>

namespace Geometry {

namespace {

std::unique_ptr<double[], decltype(&std::free)>
create_coeff(const Polygon_2& polygon)
{
    std::unique_ptr<double[], decltype(&std::free)> coeff(
        reinterpret_cast<double*>(
            std::malloc((polygon.size() + 1) * 2 * sizeof(double))),
        &std::free);
    if (!coeff) {
        throw;
    }
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        std::size_t base = index * 2;
        const Point_2& point = polygon.point(index);
        coeff[base + 0] = point.x();
        coeff[base + 1] = point.y();
    }
    const std::size_t base = polygon.size() * 2;
    const Point_2& point = polygon.point(0);
    coeff[base + 0] = point.x();
    coeff[base + 1] = point.y();
    return coeff;
}

std::unique_ptr<double[], decltype(&std::free)>
create_coeff(const Polyline_2& polyline)
{
    std::unique_ptr<double[], decltype(&std::free)> coeff(
        reinterpret_cast<double*>(
            std::malloc(polyline.size() * 2 * sizeof(double))),
        &std::free);
    if (!coeff) {
        throw;
    }
    for (std::size_t index = 0; index < polyline.size(); ++index) {
        std::size_t base = index * 2;
        const Point_2& point = polyline.point(index);
        coeff[base + 0] = point.x();
        coeff[base + 1] = point.y();
    }
    return coeff;
}

} // namespace

const std::shared_ptr<const Closed_curve_2>
Curve::create(const Circle_2& circle)
{
    const Point_2& center = circle.center();
    const double radius = circle.radius();
    double normal[2] = {0.0, 0.0};
    double centre[2] = {center.x(), center.y()};
    double ellipaxis[2] = {radius, 0.0};
    constexpr double ratio = 1.0;
    constexpr int dim = 2;
    SISLCurve* ellipse = nullptr;
    int jstat = 0;
    s1522(normal, centre, ellipaxis, ratio, dim, &ellipse, &jstat);
    std::shared_ptr<const Curve> curve(new Curve(
        std::unique_ptr<SISLCurve, decltype(&freeCurve)>(ellipse, &freeCurve)));
    return std::shared_ptr<const Closed_curve_2>(curve,
                                                 &curve->as_closed_curve_2());
}

const std::shared_ptr<const Closed_curve_2>
Curve::create(const Polygon_2& polygon)
{
    const int number = polygon.size() + 1;
    constexpr int order = 2;
    std::unique_ptr<double[], decltype(&std::free)> knots(
        reinterpret_cast<double*>(
            std::malloc((number + order) * sizeof(double))),
        &std::free);
    if (!knots) {
        throw;
    }
    const double step = 1.0 / (number - 1);
    knots[0] = 0.0 - step;
    for (std::size_t index = 0; index < number; ++index) {
        knots[index + 1] = index * step;
    }
    knots[number + 1] = 1.0 + step;
    std::unique_ptr<double[], decltype(&std::free)> coeff =
        create_coeff(polygon);
    constexpr int kind = 1;
    constexpr int dim = 2;
    constexpr int copy = 2;
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve_(
        newCurve(number, order, knots.release(), coeff.release(), kind, dim,
                 copy),
        &freeCurve);
    if (!curve_) {
        throw;
    }
    curve_->cuopen = 0;
    std::shared_ptr<const Curve> curve(new Curve(std::move(curve_)));
    return std::shared_ptr<const Closed_curve_2>(curve,
                                                 &curve->as_closed_curve_2());
}

const std::shared_ptr<const Open_curve_2>
Curve::create(const Polyline_2& polyline)
{
    const int number = polyline.size();
    constexpr int order = 2;
    std::unique_ptr<double[], decltype(&std::free)> knots(
        reinterpret_cast<double*>(
            std::malloc((polyline.size() + 2) * sizeof(double))),
        &std::free);
    if (!knots) {
        throw;
    }
    const double step = 1.0 / (number - 1);
    knots[0] = 0.0;
    for (std::size_t index = 0; index < number; ++index) {
        knots[index + 1] = index * step;
    }
    knots[number + 1] = 1.0;
    std::unique_ptr<double[], decltype(&std::free)> coeff =
        create_coeff(polyline);
    constexpr int kind = 1;
    constexpr int dim = 2;
    constexpr int copy = 2;
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve_(
        newCurve(number, order, knots.release(), coeff.release(), kind, dim,
                 copy),
        &freeCurve);
    if (!curve_) {
        throw;
    }
    std::shared_ptr<const Curve> curve(new Curve(std::move(curve_)));
    return std::shared_ptr<const Open_curve_2>(curve,
                                               &curve->as_open_curve_2());
}

const std::shared_ptr<const Closed_curve_2>
Curve::create(const Rectangle_2& rectangle)
{
    const Point_2& start = rectangle.start();
    const double x1 = start.x();
    const double y1 = start.y();
    const Point_2& end = rectangle.end();
    const double x2 = end.x();
    const double y2 = end.y();
    return Curve::create(*Polygon_2::create(
        {Point_2(x1, y1), Point_2(x2, y1), Point_2(x2, y2), Point_2(x1, y2)}));
}

const bool
Curve::is_closed() const
{
    return curve_->cuopen != 1;
}

const std::size_t
Curve::dimension() const
{
    return curve_->idim;
}

const Curve_2&
Curve::as_curve_2() const
{
    assert(dimension() == 2);
    return static_cast<const Curve_2&>(*this);
}

const Closed_curve_2&
Curve::as_closed_curve_2() const
{
    assert(is_closed() && dimension() == 2);
    return static_cast<const Closed_curve_2&>(*this);
}

const Open_curve_2&
Curve::as_open_curve_2() const
{
    assert(!is_closed() && dimension() == 2);
    return static_cast<const Open_curve_2&>(*this);
}

Curve::Curve(std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve)
    : curve_(std::move(curve))
{
}

} // namespace Geometry
