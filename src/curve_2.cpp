#include "curve_2.h"
#include "closed_curve_2.h"
#include "open_curve_2.h"
#include <cassert>

namespace Geometry {

const Point_2
Curve_2::control(const std::size_t index) const
{
    const std::size_t base = index * 2;
    const double* ecoef = curve_->ecoef;
    return Point_2(ecoef[base + 0], ecoef[base + 1]);
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
