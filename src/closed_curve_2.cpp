#include "closed_curve_2.h"
#include "polygon_2.h"

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
    double* points = nullptr;
    int numpoints = 0;
    int stat = 0;
    s1613(curve_.get(), epsge, &points, &numpoints, &stat);
    if (stat < 0) {
        throw;
    }
    std::unique_ptr<double[], decltype(&std::free)> points_1(points,
                                                             &std::free);
    std::vector<Point_2> points_2;
    for (std::size_t index = 0; index < numpoints - 1; ++index) {
        const std::size_t base = index * 2;
        points_2.push_back(Point_2(points_1[base + 0], points_1[base + 1]));
    }
    return Polygon_2::create(std::move(points_2));
}

} // namespace Geometry
