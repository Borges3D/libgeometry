#include "closed_curve_2.h"
#include "circle_2.h"
#include "polygon_2.h"
#include "rectangle_2.h"
#include "sisl_utilities.h"
#include "utilities.h"
#include <cassert>
#include <cmath>
#include <utility>

namespace Geometry {

std::shared_ptr<const Closed_curve_2>
Closed_curve_2::create(const Circle_2& c)
{
    const Point_2& center = c.center();
    const double radius = c.radius();
    double normal[2] = {0.0, 0.0};
    double centre[2] = {center.x(), center.y()};
    double ellipaxis[2] = {radius, 0.0};
    constexpr double ratio = 1.0;
    constexpr int dim = 2;
    SISLCurve* ellipse = nullptr;
    int jstat = 0;
    s1522(normal, centre, ellipaxis, ratio, dim, &ellipse, &jstat);
    return std::shared_ptr<const Closed_curve_2>(new Closed_curve_2(
        std::unique_ptr<SISLCurve, decltype(&freeCurve)>(ellipse, &freeCurve)));
}

std::shared_ptr<const Closed_curve_2>
Closed_curve_2::create(const Rectangle_2& r)
{
    const Point_2& start = r.start();
    const double x1 = start.x();
    const double y1 = start.y();
    const Point_2& end = r.end();
    const double x2 = end.x();
    const double y2 = end.y();
    return Closed_curve_2::create(*Geometry::to_polygon_2(r));
}

std::shared_ptr<const Closed_curve_2>
Closed_curve_2::create(const Polygon_2& ps)
{
    const int number = ps.size() + 1;
    constexpr int order = 2;
    const std::vector<double> ts = parameters(ps);
    std::unique_ptr<double[], decltype(&std::free)> knots(
        reinterpret_cast<double*>(
            std::malloc((ts.size() + 2) * sizeof(double))),
        &std::free);
    if (!knots) {
        throw std::runtime_error("");
    }
    knots[0] = 0.0;
    for (std::size_t index = 0; index < ts.size(); ++index) {
        knots[index + 1] = ts[index];
    }
    knots[ts.size() + 1] = 1.0;
    std::unique_ptr<double[], decltype(&std::free)> coef(
        reinterpret_cast<double*>(
            std::malloc((ps.size() + 1) * 2 * sizeof(double))),
        &std::free);
    if (!coef) {
        throw std::runtime_error("");
    }
    double* dst = coef.get();
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        *dst++ = p.x();
        *dst++ = p.y();
    }
    const Point_2& p = ps[0];
    *dst++ = p.x();
    *dst++ = p.y();
    constexpr int kind = 1;
    constexpr int dim = 2;
    constexpr int copy = 2;
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve_(
        newCurve(number, order, knots.release(), coef.release(), kind, dim,
                 copy),
        &freeCurve);
    if (!curve_) {
        throw std::runtime_error("");
    }
    curve_->cuopen = 0;
    return std::shared_ptr<const Closed_curve_2>(
        new Closed_curve_2(std::move(curve_)));
}

std::shared_ptr<const Closed_curve_2>
Closed_curve_2::fit(const std::size_t order, const Polygon_2& ps,
                    const double smoothness)
{
    std::vector<double> point;
    point.reserve((ps.size() + 1) * 2);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        point.push_back(p.x());
        point.push_back(p.y());
    }
    point.push_back(point[0]);
    point.push_back(point[1]);
    std::vector<double> derivate;
    derivate.reserve((ps.size() + 1) * 2);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        Vector_2 v1 = normalize(p - ps[(index + ps.size() - 1) % ps.size()]);
        Vector_2 v2 = normalize(ps[(index + 1) % ps.size()] - p);
        if (is_definitely_less(std::fabs(cross_product(v1, v2)), smoothness) &&
            is_definitely_less(0.0, dot_product(v1, v2))) {
            Vector_2 v = lerp(v1, v2, 0.5);
            derivate.push_back(v.x());
            derivate.push_back(v.y());
        }
        else {
            derivate.push_back(0.0);
            derivate.push_back(0.0);
        }
    }
    derivate.push_back(derivate[0]);
    derivate.push_back(derivate[1]);
    const int numpnt = ps.size() + 1;
    constexpr int dim = 2;
    constexpr int typepar = 1;
    SISLCurve* curve_ = nullptr;
    int stat = 0;
    s1380(point.data(), derivate.data(), numpnt, dim, typepar, &curve_,
          &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    return std::shared_ptr<const Closed_curve_2>(new Closed_curve_2(
        std::unique_ptr<SISLCurve, decltype(&freeCurve)>(curve_, &freeCurve)));
}

std::shared_ptr<const Closed_curve_2>
Closed_curve_2::fit(const bool is_periodic, const std::size_t order,
                    const std::vector<Point_2>& ps)
{
    return std::shared_ptr<const Closed_curve_2>(
        new Closed_curve_2(Geometry::fit(is_periodic ? -1 : 0, order, ps)));
}

std::shared_ptr<const Polygon_2>
Closed_curve_2::to_polygon_2(const double tolerance) const
{
    const double epsge = tolerance;
    double* points_ = nullptr;
    int numpoints = 0;
    int stat = 0;
    s1613(curve_.get(), epsge, &points_, &numpoints, &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    std::unique_ptr<double[], decltype(&std::free)> points(points_, &std::free);
    return Polygon_2::create(to_points_2(true, numpoints, points.get()));
}

std::vector<std::shared_ptr<const Closed_curve_2>>
offset(const Closed_curve_2& c, const Offset_options& options)
{
    std::vector<std::shared_ptr<const Closed_curve_2>> cs;
    for (const std::shared_ptr<const Polygon_2>& ps :
         offset(*c.to_polygon_2(options.tolerance), options)) {
        cs.push_back(Closed_curve_2::fit(c.order(), *ps, options.smoothness));
    }
    return cs;
}

Closed_curve_2::Closed_curve_2(
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve)
    : Curve_2(std::move(curve))
{
    assert(is_closed());
}

} // namespace Geometry
