#include "open_curve_2.h"
#include "polygon_2.h"
#include "polyline_2.h"
#include "sisl_utilities.h"

namespace Geometry {

std::shared_ptr<const Polyline_2>
Open_curve_2::to_polyline_2(const double tolerance) const
{
    const double epsge = tolerance;
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

std::vector<std::shared_ptr<const Closed_curve_2>>
offset(const Open_curve_2& c, const Offset_options& options)
{
    std::vector<std::shared_ptr<const Closed_curve_2>> cs;
    for (const std::shared_ptr<const Polygon_2>& ps :
         offset(*c.to_polyline_2(options.tolerance), options)) {
        cs.push_back(Curve::fit(c.order(), *ps, options.smoothness));
    }
    return cs;
}

} // namespace Geometry
