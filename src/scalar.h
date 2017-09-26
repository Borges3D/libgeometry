#ifndef GEOMETRY_UTILITIES_H
#define GEOMETRY_UTILITIES_H

#include <cstdint>

namespace Geometry {

const bool is_approximately_equal(const double x1, const double x2);
const bool is_definitely_less(const double x1, const double x2);
const double interpolate(const double x1, const double x2, const double t);

} // namespace Geometry

#endif // GEOMETRY_UTILITIES_H
