#include "curve_2.h"

namespace Geometry {

const Point_2
Curve_2::control(const std::size_t index) const
{
    const std::size_t base = index * 2;
    const double* ecoef = curve_->ecoef;
    return Point_2(ecoef[base + 0], ecoef[base + 1]);
}

} // namespace Geometry
