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

std::unique_ptr<SISLCurve, decltype(&freeCurve)>
fit_helper(const int iopen, const int ik, const std::vector<Point_2>& ps)
{
    std::vector<double> epoint;
    epoint.reserve(ps.size() * 2);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        epoint.push_back(p.x());
        epoint.push_back(p.y());
    }
    const int inbpnt = ps.size();
    constexpr int idim = 2;
    std::vector<int> nptyp;
    nptyp.reserve(ps.size());
    for (std::size_t index = 0; index < ps.size(); ++index) {
        nptyp.push_back(1);
    }
    constexpr int icnsta = 0;
    constexpr int icnend = 0;
    const double astpar = 0.0;
    double cendpar = 0.0;
    SISLCurve* rc_ = nullptr;
    double* gpar_ = nullptr;
    int jnbpar = 0;
    int jstat = 0;
    s1356(epoint.data(), inbpnt, idim, nptyp.data(), icnsta, icnend, iopen, ik,
          astpar, &cendpar, &rc_, &gpar_, &jnbpar, &jstat);
    if (jstat < 0) {
        throw;
    }
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> rc(rc_, &freeCurve);
    std::unique_ptr<double[], decltype(&std::free)> gpar(gpar_, &std::free);
    return rc;
}

} // namespace

const std::shared_ptr<const Closed_curve_2>
Curve::create(const Circle_2& c)
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
    std::shared_ptr<const Curve> curve(new Curve(
        std::unique_ptr<SISLCurve, decltype(&freeCurve)>(ellipse, &freeCurve)));
    return std::shared_ptr<const Closed_curve_2>(curve,
                                                 &curve->as_closed_curve_2());
}

const std::shared_ptr<const Closed_curve_2>
Curve::create(const Polygon_2& ps)
{
    const int number = ps.size() + 1;
    constexpr int order = 2;
    const std::vector<double> ts = parameters(ps);
    std::unique_ptr<double[], decltype(&std::free)> knots(
        reinterpret_cast<double*>(
            std::malloc((ts.size() + 2) * sizeof(double))),
        &std::free);
    if (!knots) {
        throw;
    }
    knots[0] = 0.0;
    for (std::size_t index = 0; index < ts.size(); ++index) {
        knots[index + 1] = ts[index];
    }
    knots[ts.size() + 1] = 1.0;
    std::unique_ptr<double[], decltype(&std::free)> coeff(
        reinterpret_cast<double*>(
            std::malloc((ps.size() + 1) * 2 * sizeof(double))),
        &std::free);
    if (!coeff) {
        throw;
    }
    for (std::size_t index = 0; index < ps.size(); ++index) {
        std::size_t base = index * 2;
        const Point_2& p = ps[index];
        coeff[base + 0] = p.x();
        coeff[base + 1] = p.y();
    }
    const std::size_t base = ps.size() * 2;
    const Point_2& p = ps[0];
    coeff[base + 0] = p.x();
    coeff[base + 1] = p.y();
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
Curve::create(const Polyline_2& ps)
{
    const int number = ps.size();
    constexpr int order = 2;
    const std::vector<double> ts = parameters(ps);
    std::unique_ptr<double[], decltype(&std::free)> knots(
        reinterpret_cast<double*>(
            std::malloc((ts.size() + 2) * sizeof(double))),
        &std::free);
    if (!knots) {
        throw;
    }
    knots[0] = ts[0];
    for (std::size_t index = 0; index < ts.size(); ++index) {
        knots[index + 1] = ts[index];
    }
    knots[ts.size() + 1] = ts[ts.size() - 1];
    std::unique_ptr<double[], decltype(&std::free)> coeff(
        reinterpret_cast<double*>(
            std::malloc(ps.size() * 2 * sizeof(double))),
        &std::free);
    if (!coeff) {
        throw;
    }
    for (std::size_t index = 0; index < ps.size(); ++index) {
        std::size_t base = index * 2;
        const Point_2& p = ps[index];
        coeff[base + 0] = p.x();
        coeff[base + 1] = p.y();
    }
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
Curve::create(const Rectangle_2& r)
{
    const Point_2& start = r.start();
    const double x1 = start.x();
    const double y1 = start.y();
    const Point_2& end = r.end();
    const double x2 = end.x();
    const double y2 = end.y();
    return Curve::create(*Polygon_2::create(
        {Point_2(x1, y1), Point_2(x2, y1), Point_2(x2, y2), Point_2(x1, y2)}));
}

const std::shared_ptr<const Closed_curve_2>
Curve::fit_closed(const bool periodic, const std::size_t order,
                  const std::vector<Point_2>& ps)
{
    std::shared_ptr<const Curve> curve(
        new Curve(fit_helper(periodic ? -1 : 0, order, ps)));
    return std::shared_ptr<const Closed_curve_2>(curve,
                                                 &curve->as_closed_curve_2());
}

const std::shared_ptr<const Open_curve_2>
Curve::fit_open(const std::size_t order, const std::vector<Point_2>& ps)
{
    std::shared_ptr<const Curve> curve(new Curve(fit_helper(1, order, ps)));
    return std::shared_ptr<const Open_curve_2>(curve,
                                               &curve->as_open_curve_2());
}

const bool
Curve::is_closed() const
{
    return curve_->cuopen != 1;
}

const std::size_t
Curve::size() const
{
    return curve_->in;
}

const std::size_t
Curve::order() const
{
    return curve_->ik;
}

const std::size_t
Curve::dimension() const
{
    return curve_->idim;
}

const double
Curve::knot(const std::size_t index) const
{
    assert(index < size() + order());
    return curve_->et[index];
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
