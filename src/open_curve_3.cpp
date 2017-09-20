#include "open_curve_3.h"
#include "polyline_3.h"
#include "sisl_utilities.h"
#include "unique_malloc_ptr.h"
#include "utilities.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <utility>

namespace Geometry {

std::shared_ptr<const Open_curve_3>
Open_curve_3::create(const Polyline_3& ps)
{
    const std::vector<double> ts = parameters(ps);
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
            std::malloc(ps.size() * 3 * sizeof(double))),
        &std::free);
    if (!coef) {
        throw std::runtime_error("");
    }
    double* dst = coef.get();
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_3& p = ps[index];
        *dst++ = p.x();
        *dst++ = p.y();
        *dst++ = p.y();
    }
    const int number = ps.size();
    constexpr int order = 2;
    double* knots_ptr = knots.release();
    double* coef_ptr = coef.release();
    constexpr int kind = 1;
    constexpr int dim = 3;
    constexpr int copy = 2;
    Internal::Unique_sisl_curve_ptr curve(
        newCurve(number, order, knots_ptr, coef_ptr, kind, dim, copy));
    if (!curve) {
        throw std::runtime_error("");
    }
    return std::shared_ptr<const Open_curve_3>(
        new Open_curve_3(std::move(curve)));
}

std::shared_ptr<const Open_curve_3>
Open_curve_3::fit(const std::size_t order, const std::vector<Point_3>& ps)
{
    return std::shared_ptr<const Open_curve_3>(
        new Open_curve_3(Internal::fit(1, order, ps)));
}

std::shared_ptr<const Open_curve_3>
Open_curve_3::fit(const std::size_t order, const Polyline_3& ps,
                  const double smoothness)
{
    std::vector<double> point;
    point.reserve(ps.size() * 3);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_3& p = ps[index];
        point.push_back(p.x());
        point.push_back(p.y());
        point.push_back(p.z());
    }
    std::vector<double> derivate;
    derivate.reserve(ps.size() * 3);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_3& p = ps[index];
        Vector_3 v1 =
            normalize(p - ps[std::max(static_cast<std::size_t>(0), index - 1)]);
        Vector_3 v2 = normalize(ps[std::min(index + 1, ps.size())] - p);
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
    double* point_ptr = point.data();
    double* derivate_ptr = derivate.data();
    const int numpnt = ps.size();
    constexpr int dim = 3;
    constexpr int typepar = 1;
    SISLCurve* curve_ptr = nullptr;
    int stat = 0;
    s1380(point_ptr, derivate_ptr, numpnt, dim, typepar, &curve_ptr,
          &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    return std::shared_ptr<const Open_curve_3>(
        new Open_curve_3(Internal::Unique_sisl_curve_ptr(curve_ptr)));
}

std::tuple<std::shared_ptr<const Open_curve_3>,
           std::shared_ptr<const Open_curve_3>>
Open_curve_3::split(const double u) const
{
    std::tuple<Internal::Unique_sisl_curve_ptr, Internal::Unique_sisl_curve_ptr>
        rcnew1_rcnew2 = Internal::split(curve_.get(), u);
    return std::make_tuple(std::shared_ptr<const Open_curve_3>(new Open_curve_3(
                               std::move(std::get<0>(rcnew1_rcnew2)))),
                           std::shared_ptr<const Open_curve_3>(new Open_curve_3(
                               std::move(std::get<1>(rcnew1_rcnew2)))));
}

std::shared_ptr<const Polyline_3>
Open_curve_3::to_polyline_3(const double tolerance) const
{
    SISLCurve* curve_ptr = curve_.get();
    const double epsge = tolerance;
    double* points_ptr = nullptr;
    int numpoints = 0;
    int stat = 0;
    s1613(curve_ptr, epsge, &points_ptr, &numpoints, &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    Internal::Unique_malloc_ptr<double[]> points(points_ptr);
    const double* src = points.get();
    std::vector<Point_3> ps;
    const double x = *src++;
    const double y = *src++;
    const double z = *src++;
    ps.push_back(Point_3(x, y, z));
    for (std::size_t index = 1; index < numpoints; ++index) {
        const double x = *src++;
        const double y = *src++;
        const double z = *src++;
        Point_3 p(x, y, z);
        if (!is_approximately_equal(p, ps.back())) {
            ps.push_back(p);
        }
    }
    return Polyline_3::create(ps);
}

Open_curve_3::Open_curve_3(Internal::Unique_sisl_curve_ptr curve)
    : Curve_3(std::move(curve))
{
}

} // namespace Geometry
