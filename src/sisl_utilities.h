#ifndef GEOMETRY_SISL_UTILITIES_H
#define GEOMETRY_SISL_UTILITIES_H

#include "unique_sisl_curve_ptr.h"
#include <tuple>
#include <vector>

namespace Geometry {

class Point_2;
class Point_3;

namespace Internal {

Unique_sisl_curve_ptr
fit(const int iopen, const int ik, const std::vector<Point_2>& ps);
Unique_sisl_curve_ptr
fit(const int iopen, const int ik, const std::vector<Point_3>& ps);
std::tuple<Unique_sisl_curve_ptr, Unique_sisl_curve_ptr>
split(SISLCurve* pc1_ptr, const double apar);

} // namespace Internal

} // namespace Geometry

#endif // GEOMETRY_SISL_UTILITIES_H
