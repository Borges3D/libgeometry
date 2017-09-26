#include "open_curve_2.h"
#include "closed_curve_2.h"
#include "polygon_2.h"
#include "polyline_2.h"
#include "scalar.h"
#include "sisl_utilities.h"
#include "unique_malloc_ptr.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <utility>

namespace Geometry {

std::shared_ptr<const Open_curve_2>
Open_curve_2::create(const Polyline_2& ps)
{
    const std::vector<double> ts = Geometry::parameters(ps);
    std::unique_ptr<double[], decltype(&std::free)> knots(
        reinterpret_cast<double*>(
            std::malloc((ts.size() + 2) * sizeof(double))),
        &std::free);
    if (!knots) {
        throw std::runtime_error("");
    }
    knots[0] = ts[0];
    for (std::size_t index = 0; index < ts.size(); ++index) {
        knots[index + 1] = ts[index];
    }
    knots[ts.size() + 1] = ts[ts.size() - 1];
    std::unique_ptr<double[], decltype(&std::free)> coef(
        reinterpret_cast<double*>(
            std::malloc(ps.size() * 2 * sizeof(double))),
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
    const int number = ps.size();
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
    return std::shared_ptr<const Open_curve_2>(
        new Open_curve_2(std::move(curve)));
}

std::shared_ptr<const Open_curve_2>
Open_curve_2::fit(const std::size_t order, const std::vector<Point_2>& ps)
{
    return std::shared_ptr<const Open_curve_2>(
        new Open_curve_2(Internal::fit(1, order, ps)));
}

std::shared_ptr<const Open_curve_2>
Open_curve_2::fit(const std::size_t order, const Polyline_2& ps,
                  const double smoothness)
{
    std::vector<double> point;
    point.reserve(ps.size() * 2);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        point.push_back(p.x());
        point.push_back(p.y());
    }
    std::vector<double> derivate;
    derivate.reserve(ps.size() * 2);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        Vector_2 v1 =
            normalize(p - ps[std::max(static_cast<std::size_t>(0), index - 1)]);
        Vector_2 v2 = normalize(ps[std::min(index + 1, ps.size())] - p);
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
    double* point_ptr = point.data();
    double* derivate_ptr = derivate.data();
    const int numpnt = ps.size();
    constexpr int dim = 2;
    constexpr int typepar = 1;
    SISLCurve* curve_ptr = nullptr;
    int stat = 0;
    s1380(point_ptr, derivate_ptr, numpnt, dim, typepar, &curve_ptr, &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    return std::shared_ptr<const Open_curve_2>(
        new Open_curve_2(Internal::Unique_sisl_curve_ptr(curve_ptr)));
}

std::tuple<std::shared_ptr<const Open_curve_2>,
           std::shared_ptr<const Open_curve_2>>
Open_curve_2::split(const double u) const
{
    std::tuple<Internal::Unique_sisl_curve_ptr, Internal::Unique_sisl_curve_ptr>
        rcnew1_rcnew2 = Internal::split(curve_.get(), u);
    return std::make_tuple(std::shared_ptr<const Open_curve_2>(new Open_curve_2(
                               std::move(std::get<0>(rcnew1_rcnew2)))),
                           std::shared_ptr<const Open_curve_2>(new Open_curve_2(
                               std::move(std::get<1>(rcnew1_rcnew2)))));
}

Open_curve_2::Open_curve_2(Internal::Unique_sisl_curve_ptr curve)
    : Curve_2(std::move(curve))
{
    assert(!is_closed());
}

std::vector<std::shared_ptr<const Closed_curve_2>>
offset(const Open_curve_2& c, const Offset_options& options)
{
    std::vector<std::shared_ptr<const Closed_curve_2>> cs;
    for (const std::shared_ptr<const Polygon_2>& ps :
         offset(*linearize(c, options.tolerance), options)) {
        cs.push_back(Closed_curve_2::fit(c.order(), *ps, options.smoothness));
    }
    return cs;
}

std::shared_ptr<const Polyline_2>
linearize(const Open_curve_2& c, const double tolerance)
{
    std::vector<double> us = c.parameters(tolerance);
    std::vector<Point_2> ps;
    ps.push_back(c.point(us[0]));
    for (std::size_t index = 1; index < us.size(); ++index) {
        Point_2 p = c.point(us[index]);
        if (!is_approximately_equal(p, ps.back())) {
            ps.push_back(p);
        }
    }
    return Polyline_2::create(ps);
}

} // namespace Geometry
