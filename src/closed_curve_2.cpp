#include "closed_curve_2.h"
#include "polygon_2.h"
#include "sisl_utilities.h"

namespace Geometry {

bool
Closed_curve_2::is_periodic() const
{
    return curve_->cuopen = -1;
}

const std::shared_ptr<const Polygon_2>
Closed_curve_2::to_polygon_2(const double epsilon) const
{
    const double epsge = epsilon;
    double* points_ = nullptr;
    int numpoints = 0;
    int stat = 0;
    s1613(curve_.get(), epsge, &points_, &numpoints, &stat);
    if (stat < 0) {
        throw;
    }
    std::unique_ptr<double[], decltype(&std::free)> points(points_, &std::free);
    return Polygon_2::create(to_points(true, numpoints, points.get()));
}

} // namespace Geometry
