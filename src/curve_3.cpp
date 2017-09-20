#include "curve_3.h"
#include "closed_curve_3.h"
#include "open_curve_3.h"
#include <cassert>
#include <utility>

namespace Geometry {

const Point_3
Curve_3::control(const std::size_t index) const
{
    const int ikind = curve_->ikind;
    if (ikind == 1 || ikind == 3) {
        const double* ecoef = curve_->ecoef;
        const std::size_t base = index * 3;
        return Point_3(ecoef[base + 0], ecoef[base + 1], ecoef[base + 2]);
    }
    else {
        const double* rcoef = curve_->rcoef;
        const std::size_t base = index * 4;
        return Point_3(rcoef[base + 0], rcoef[base + 1], rcoef[base + 2]);
    }
}

const Closed_curve_3&
Curve_3::as_closed_curve_3() const
{
    assert(is_closed());
    return static_cast<const Closed_curve_3&>(*this);
}

const Open_curve_3&
Curve_3::as_open_curve_3() const
{
    assert(!is_closed());
    return static_cast<const Open_curve_3&>(*this);
}

Curve_3::Curve_3(Internal::Unique_sisl_curve_ptr curve)
    : Curve(std::move(curve))
{
    assert(dimension() == 3);
}

} // namespace Geometry
