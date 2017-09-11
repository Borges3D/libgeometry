#include "curve.h"
#include "curve_2.h"
#include "curve_3.h"
#include <cassert>

namespace Geometry {

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

const Curve_3&
Curve::as_curve_3() const
{
    assert(dimension() == 3);
    return static_cast<const Curve_3&>(*this);
}

Curve::Curve(std::unique_ptr<SISLCurve, decltype(&freeCurve)> curve)
    : curve_(std::move(curve))
{
}

} // namespace Geometry
