#include "curve_2.h"
#include "closed_curve_2.h"
#include "curve_3.h"
#include "open_curve_2.h"
#include <cassert>
#include <utility>

namespace Geometry {

const Point_2
Curve_2::control(const std::size_t index) const
{
    const int ikind = curve_->ikind;
    if (ikind == 1 || ikind == 3) {
        const double* ecoef = curve_->ecoef;
        const std::size_t base = index * 2;
        return Point_2(ecoef[base + 0], ecoef[base + 1]);
    }
    else {
        const double* rcoef = curve_->rcoef;
        const std::size_t base = index * 3;
        return Point_2(rcoef[base + 0], rcoef[base + 1]);
    }
}

const Closed_curve_2&
Curve_2::as_closed_curve_2() const
{
    assert(is_closed());
    return static_cast<const Closed_curve_2&>(*this);
}

const Open_curve_2&
Curve_2::as_open_curve_2() const
{
    assert(!is_closed());
    return static_cast<const Open_curve_2&>(*this);
}

std::shared_ptr<const Curve_3>
Curve_2::to_curve_3() const
{
    const int number = curve_->in;
    const int order = curve_->ik;
    const std::size_t knots_size = curve_->in + curve_->ik;
    std::unique_ptr<double[], decltype(&std::free)> knots(
        reinterpret_cast<double*>(std::malloc(knots_size * sizeof(double))),
        &std::free);
    if (!knots) {
        throw std::runtime_error("");
    }
    for (std::size_t index = 0; index < knots_size; ++index) {
        knots[index] = curve_->et[index];
    }
    const bool is_rational = curve_->ikind == 2 || curve_->ikind == 4;
    const std::size_t vertex_size = is_rational ? 4 : 3;
    std::unique_ptr<double[], decltype(&std::free)> coef(
        reinterpret_cast<double*>(
            std::malloc(curve_->in * vertex_size * sizeof(double))),
        &std::free);
    if (!coef) {
        throw std::runtime_error("");
    }
    double* dst = coef.get();
    if (is_rational) {
        const double* src = curve_->rcoef;
        for (std::size_t index = 0; index < curve_->in; ++index) {
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = 0.0;
            *dst++ = *src++;
        }
    }
    else {
        const double* src = curve_->ecoef;
        for (std::size_t index = 0; index < curve_->in; ++index) {
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = 0.0;
        }
    }
    const int kind = curve_->ikind;
    constexpr int dim = 3;
    constexpr int copy = 2;
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve(
        newCurve(number, order, knots.release(), coef.release(), kind, dim,
                 copy),
        &freeCurve);
    curve->cuopen = curve_->cuopen;
    return std::shared_ptr<const Curve_3>(new Curve_3(std::move(curve)));
}

Curve_2::Curve_2(std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve)
    : Curve(std::move(curve))
{
    assert(dimension() == 2);
}

std::vector<std::shared_ptr<const Curve_2>>
offset(const Curve_2& c, const Offset_options& options)
{
    std::vector<std::shared_ptr<const Curve_2>> cs;
    if (c.is_closed()) {
        for (const std::shared_ptr<const Closed_curve_2>& c :
             offset(c.as_closed_curve_2(), options)) {
            cs.push_back(std::shared_ptr<const Curve_2>(c, c.get()));
        }
    }
    else {
        for (const std::shared_ptr<const Closed_curve_2>& c :
             offset(c.as_open_curve_2(), options)) {
            cs.push_back(std::shared_ptr<const Curve_2>(c, c.get()));
        }
    }
    return cs;
}

} // namespace Geometry
