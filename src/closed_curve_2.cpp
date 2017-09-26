#include "closed_curve_2.h"
#include "circle.h"
#include "open_curve_2.h"
#include "rectangle.h"
#include "scalar.h"
#include "simple_polygon.h"
#include "sisl_utilities.h"
#include "unique_malloc_ptr.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <stdexcept>

namespace Geometry {

std::shared_ptr<const Closed_curve_2>
Closed_curve_2::create(const Circle& c)
{
    const Point_2& center = c.center();
    const double radius = c.radius();
    double normal[2] = {0.0, 0.0};
    double centre[2] = {center.x(), center.y()};
    double ellipaxis[2] = {radius, 0.0};
    constexpr double ratio = 1.0;
    constexpr int dim = 2;
    SISLCurve* ellipse_ptr = nullptr;
    int jstat = 0;
    s1522(normal, centre, ellipaxis, ratio, dim, &ellipse_ptr, &jstat);
    return std::shared_ptr<const Closed_curve_2>(
        new Closed_curve_2(Internal::Unique_sisl_curve_ptr(ellipse_ptr)));
}

std::shared_ptr<const Closed_curve_2>
Closed_curve_2::create(const Rectangle& r)
{
    return Closed_curve_2::create(*to_simple_polygon(r));
}

std::shared_ptr<const Closed_curve_2>
Closed_curve_2::create(const Polygon_2& ps)
{
    const std::vector<double> ts = Geometry::parameters(ps);
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
    const int number = ps.size() + 1;
    constexpr int order = 2;
    double* knots_ptr = knots.release();
    double* coef_ptr = coef.release();
    constexpr int kind = 1;
    constexpr int dim = 2;
    constexpr int copy = 2;
    Internal::Unique_sisl_curve_ptr curve(
        newCurve(number, order, knots_ptr, coef_ptr, kind, dim, copy));
    if (!curve) {
        throw std::runtime_error("");
    }
    curve->cuopen = 0;
    return std::shared_ptr<const Closed_curve_2>(
        new Closed_curve_2(std::move(curve)));
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
            Vector_2 v = interpolate(v1, v2, 0.5);
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
    double* point_ptr = point.data();
    double* derivate_ptr = derivate.data();
    const int numpnt = ps.size() + 1;
    constexpr int dim = 2;
    constexpr int typepar = 1;
    SISLCurve* curve_ptr = nullptr;
    int stat = 0;
    s1380(point_ptr, derivate_ptr, numpnt, dim, typepar, &curve_ptr, &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    return std::shared_ptr<const Closed_curve_2>(
        new Closed_curve_2(Internal::Unique_sisl_curve_ptr(curve_ptr)));
}

std::shared_ptr<const Closed_curve_2>
Closed_curve_2::fit(const bool is_periodic, const std::size_t order,
                    const std::vector<Point_2>& ps)
{
    return std::shared_ptr<const Closed_curve_2>(
        new Closed_curve_2(Internal::fit(is_periodic ? -1 : 0, order, ps)));
}

const bool
Closed_curve_2::is_periodic() const
{
    return curve_->cuopen == -1;
}

std::shared_ptr<const Open_curve_2>
Closed_curve_2::split(const double u) const
{
    std::tuple<Internal::Unique_sisl_curve_ptr, Internal::Unique_sisl_curve_ptr>
        rcnew1_rcnew2 = Internal::split(curve_.get(), u);
    Internal::Unique_sisl_curve_ptr rcnew1 =
        std::move(std::get<0>(rcnew1_rcnew2));
    Internal::Unique_sisl_curve_ptr rcnew2 =
        std::move(std::get<1>(rcnew1_rcnew2));
    if (rcnew1) {
        assert(!rcnew2);
        return std::shared_ptr<Open_curve_2>(
            new Open_curve_2(std::move(rcnew1)));
    }
    else {
        assert(rcnew2);
        return std::shared_ptr<Open_curve_2>(
            new Open_curve_2(std::move(rcnew2)));
    }
}

std::vector<std::shared_ptr<const Closed_curve_2>>
clip(const std::vector<std::reference_wrapper<const Closed_curve_2>>& cs1, 
     const std::vector<std::reference_wrapper<const Closed_curve_2>>& cs2, 
     const Clip_options& options)
{
    std::size_t order = 0;
    std::vector<std::shared_ptr<const Polygon_2>> pss1;
    for (const Closed_curve_2& c : cs1) {
        order = std::max(order, c.order());
        pss1.push_back(linearize(c, options.tolerance));
    }
    std::vector<std::shared_ptr<const Polygon_2>> pss2;
    for (const Closed_curve_2& c : cs2) {
        order = std::max(order, c.order());
        pss2.push_back(linearize(c, options.tolerance));
    }
    std::vector<std::reference_wrapper<const Polygon_2>> ps_refs_1;
    for (const std::shared_ptr<const Polygon_2> ps : pss1) {
        ps_refs_1.push_back(*ps);
    }
    std::vector<std::reference_wrapper<const Polygon_2>> ps_refs_2;
    for (const std::shared_ptr<const Polygon_2> ps : pss2) {
        ps_refs_2.push_back(*ps);
    }
    std::vector<std::shared_ptr<const Closed_curve_2>> cs;
    for (const std::shared_ptr<const Simple_polygon>& ps :
         clip(ps_refs_1, ps_refs_2, options)) {
        cs.push_back(Closed_curve_2::fit(order, *ps, options.smoothness));
    }
    return cs;
}

std::vector<std::shared_ptr<const Closed_curve_2>>
offset(const Closed_curve_2& c, const Offset_options& options)
{
    std::vector<std::shared_ptr<const Closed_curve_2>> cs;
    for (const std::shared_ptr<const Polygon_2>& ps :
         offset(*linearize(c, options.tolerance), options)) {
        cs.push_back(Closed_curve_2::fit(c.order(), *ps, options.smoothness));
    }
    return cs;
}

Closed_curve_2::Closed_curve_2(Internal::Unique_sisl_curve_ptr curve)
    : Curve_2(std::move(curve))
{
    assert(is_closed());
}

std::shared_ptr<const Polygon_2>
linearize(const Closed_curve_2& c, const double tolerance)
{
    std::vector<double> us = c.parameters(tolerance);
    std::vector<Point_2> ps;
    ps.push_back(c.point(us[0]));
    for (std::size_t index = 1; index < us.size() - 1; ++index) {
        Point_2 p = c.point(us[index]);
        if (!is_approximately_equal(p, ps.back())) {
            ps.push_back(p);
        }
    }
    return Polygon_2::create(ps);
}

} // namespace Geometry
