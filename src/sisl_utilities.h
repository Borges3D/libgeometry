#ifndef GEOMETRY_SISL_UTILITIES_H
#define GEOMETRY_SISL_UTILITIES_H

#include <sisl.h>
#include <vector>

namespace Geometry {

class Point_2;
class Point_3;

std::unique_ptr<SISLCurve, decltype(&freeCurve)>
fit(const int iopen, const int ik, const std::vector<Point_2>& ps);
std::unique_ptr<SISLCurve, decltype(&freeCurve)>
fit(const int iopen, const int ik, const std::vector<Point_3>& ps);
const std::vector<Point_2>
to_points_2(const bool is_closed, const std::size_t size, const double* points);
const std::vector<Point_3>
to_points_3(const bool is_closed, const std::size_t size, const double* points);

} // namespace Geometry

#endif // GEOMETRY_SISL_UTILITIES_H
