#ifndef GEOMETRY_SISL_UTILITIES_H
#define GEOMETRY_SISL_UTILITIES_H

#include <vector>

namespace Geometry {

class Point_2;

const std::vector<Point_2> to_points(bool is_closed, const std::size_t size,
                                     const double* points);

} // namespace Geometry

#endif // GEOMETRY_SISL_UTILITIES_H
