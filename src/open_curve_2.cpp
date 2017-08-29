#include "open_curve_2.h"
#include "polyline_2.h"
#include "sisl_utilities.h"

namespace Geometry {

const std::shared_ptr<const Polyline_2>
Open_curve_2::to_polyline_2(const double epsilon) const
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
    return Polyline_2::create(to_points(false, numpoints, points.get()));
}

} // namespace Geometry
