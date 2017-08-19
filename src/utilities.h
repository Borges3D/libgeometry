#ifndef GEOMETRY_UTILITIES_H
#define GEOMETRY_UTILITIES_H

#include <cstdint>

namespace Geometry {

constexpr double absolute_epsilon = 1E-6;

std::int64_t to_fixed(double x);
double to_float(std::int64_t x);

} // namespace Geometry

#endif // GEOMETRY_UTILITIES_H
