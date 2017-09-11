#include "open_curve_3.h"
#include "polyline_3.h"
#include "sisl_utilities.h"
#include "utilities.h"
#include <algorithm>
#include <cmath>
#include <utility>

namespace Geometry {

std::shared_ptr<const Open_curve_3>
Open_curve_3::create(const Polyline_3& ps)
{
    const int number = ps.size();
    constexpr int order = 2;
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
    constexpr int kind = 1;
    constexpr int dim = 3;
    constexpr int copy = 2;
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve(
        newCurve(number, order, knots.release(), coef.release(), kind, dim,
                 copy),
        &freeCurve);
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
        new Open_curve_3(Geometry::fit(1, order, ps)));
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
    const int numpnt = ps.size();
    constexpr int dim = 3;
    constexpr int typepar = 1;
    SISLCurve* curve_ = nullptr;
    int stat = 0;
    s1380(point.data(), derivate.data(), numpnt, dim, typepar, &curve_,
          &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    return std::shared_ptr<const Open_curve_3>(new Open_curve_3(
        std::unique_ptr<SISLCurve, decltype(&freeCurve)>(curve_, &freeCurve)));
}


std::shared_ptr<const Polyline_3>
Open_curve_3::to_polyline_3(const double tolerance) const
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
    return Polyline_3::create(to_points_3(false, numpoints, points.get()));
}

Open_curve_3::Open_curve_3(
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve)
    : Curve_3(std::move(curve))
{
}

} // namespace Geometry
