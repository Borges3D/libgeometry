#include "curve.h"
#include "curve_2.h"
#include "curve_3.h"
#include <cassert>

namespace Geometry {

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

const std::size_t
Curve::dimension() const
{
    return curve_->idim;
}

const bool
Curve::is_closed() const
{
    return curve_->cuopen != 1;
}

const double
Curve::knot(const std::size_t index) const
{
    assert(index < size() + order());
    return curve_->et[index];
}

const std::size_t
Curve::order() const
{
    return curve_->ik;
}

const std::size_t
Curve::size() const
{
    return curve_->in;
}

const double
Curve::u_min() const
{
    double startpar = 0.0;
    double endpar = 0.0;
    int stat = 0;
    s1363(curve_.get(), &startpar, &endpar, &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    return startpar;
}

const double
Curve::u_max() const
{
    double startpar = 0.0;
    double endpar = 0.0;
    int stat = 0;
    s1363(curve_.get(), &startpar, &endpar, &stat);
    if (stat < 0) {
        throw std::runtime_error("");
    }
    return endpar;
}

Curve::Curve(Internal::Unique_sisl_curve_ptr curve) : curve_(std::move(curve))
{
    assert(curve_ != nullptr);
}

} // namespace Geometry
