#ifndef GEOMETRY_UTILITIES_H
#define GEOMETRY_UTILITIES_H

#include <cstdint>

namespace Geometry {

constexpr double absolute_epsilon = 1E-6;

const bool is_approximately_equal(const double x1, const double x2);
const std::int64_t to_fixed(const double x);
const double to_float(const std::int64_t x);

} // namespace Geometry

#endif // GEOMETRY_UTILITIES_H
