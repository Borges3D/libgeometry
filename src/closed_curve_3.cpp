#include "closed_curve_3.h"
#include "open_curve_3.h"
#include "polygon_3.h"
#include "sisl_utilities.h"
#include "unique_malloc_ptr.h"
#include "utilities.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <utility>

namespace Geometry {

std::shared_ptr<const Closed_curve_3>
Closed_curve_3::create(const Polygon_3& ps)
{
    constexpr int order = 2;
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
            std::malloc((ps.size() + 1) * 3 * sizeof(double))),
        &std::free);
    if (!coef) {
        throw std::runtime_error("");
    }
    double* dst = coef.get();
    for (std::size_t index = 0; index < ps.size(); ++index) {
        std::size_t base = index * 3;
        const Point_3& p = ps[index];
        *dst++ = p.x();
        *dst++ = p.y();
        *dst++ = p.z();
    }
    const std::size_t base = ps.size() * 3;
    const Point_3& p = ps[0];
    *dst++ = p.x();
    *dst++ = p.y();
    *dst++ = p.z();
    const int number = ps.size() + 1;
    constexpr int kind = 1;
    double* knots_ptr = knots.release();
    double* coef_ptr = coef.release();
    constexpr int dim = 3;
    constexpr int copy = 2;
    Internal::Unique_sisl_curve_ptr curve(
        newCurve(number, order, knots_ptr, coef_ptr, kind, dim, copy));
    if (!curve) {
        throw std::runtime_error("");
    }
    curve->cuopen = 0;
    return std::shared_ptr<const Closed_curve_3>(
        new Closed_curve_3(std::move(curve)));
}

std::shared_ptr<const Closed_curve_3>
Closed_curve_3::fit(const std::size_t order, const Polygon_3& ps,
                    const double smoothness)
{
    std::vector<double> point;
    point.reserve((ps.size() + 1) * 3);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_3& p = ps[index];
        point.push_back(p.x());
        point.push_back(p.y());
        point.push_back(p.z());
    }
    point.push_back(point[0]);
    point.push_back(point[1]);
    point.push_back(point[2]);
    std::vector<double> derivate;
    derivate.reserve((ps.size() + 1) * 3);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_3& p = ps[index];
        Vector_3 v1 = normalize(p - ps[(index + ps.size() - 1) % ps.size()]);
        Vector_3 v2 = normalize(ps[(index + 1) % ps.size()] - p);
        if (is_definitely_less(std::fabs(length(cross_product(v1, v2))),
                               smoothness) &&
            is_definitely_less(0.0, dot_product(v1, v2))) {
            Vector_3 v = lerp(v1, v2, 0.5);
            derivate.push_back(v.x());
            derivate.push_back(v.y());
            derivate.push_back(v.z());
        }
        else {
            derivate.push_back(0.0);
            derivate.push_back(0.0);
            derivate.push_back(0.0);
        }
    }
    derivate.push_back(derivate[0]);
    derivate.push_back(derivate[1]);
    derivate.push_back(derivate[2]);
    double* point_ptr = point.data();
    double* derivate_ptr = derivate.data();
    const int numpnt = ps.size() + 1;
    constexpr int dim = 3;
    constexpr int typepar = 1;
    SISLCurve* curve_ptr = nullptr;
    int stat = 0;
    s1380(point_ptr, derivate_ptr, numpnt, dim, typepar, &curve_ptr, &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    return std::shared_ptr<const Closed_curve_3>(
        new Closed_curve_3(Internal::Unique_sisl_curve_ptr(curve_ptr)));
}

std::shared_ptr<const Closed_curve_3>
Closed_curve_3::fit(const bool is_periodic, const std::size_t order,
                    const std::vector<Point_3>& ps)
{
    return std::shared_ptr<const Closed_curve_3>(
        new Closed_curve_3(Internal::fit(is_periodic ? -1 : 0, order, ps)));
}

std::shared_ptr<const Open_curve_3>
Closed_curve_3::split(const double u) const
{
    std::tuple<Internal::Unique_sisl_curve_ptr, Internal::Unique_sisl_curve_ptr>
        rcnew1_rcnew2 = Internal::split(curve_.get(), u);
    Internal::Unique_sisl_curve_ptr rcnew1 =
        std::move(std::get<0>(rcnew1_rcnew2));
    Internal::Unique_sisl_curve_ptr rcnew2 =
        std::move(std::get<1>(rcnew1_rcnew2));
    if (rcnew1) {
        assert(!rcnew2);
        return std::shared_ptr<Open_curve_3>(
            new Open_curve_3(std::move(rcnew1)));
    }
    else {
        assert(rcnew2);
        return std::shared_ptr<Open_curve_3>(
            new Open_curve_3(std::move(rcnew2)));
    }
}

Closed_curve_3::Closed_curve_3(Internal::Unique_sisl_curve_ptr curve)
    : Curve_3(std::move(curve))
{
}

std::shared_ptr<const Polygon_3>
to_polygon_3(const Closed_curve_3& c, const double tolerance)
{
    std::vector<double> us = c.parameters(tolerance);
    std::vector<Point_3> ps;
    ps.push_back(c.point(us[0]));
    for (std::size_t index = 1; index < us.size() - 1; ++index) {
        Point_3 p = c.point(us[index]);
        if (!is_approximately_equal(p, ps.back())) {
            ps.push_back(p);
        }
    }
    return Polygon_3::create(ps);
}

} // namespace Geometry
