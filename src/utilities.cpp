#include "utilities.h"
#include <cassert>
#include <cmath>

namespace Geometry {

namespace {

constexpr double absolute_epsilon = 1E-6;
constexpr int fractional_bits = 32;
constexpr double relative_epsilon = 1E-6;

} // namespace

const bool
is_approximately_equal(const double x1, const double x2)
{
    const double abs_delta_x = std::abs(x1 - x2);
    return abs_delta_x < absolute_epsilon ||
           (abs_delta_x / std::abs(x1) < relative_epsilon &&
            abs_delta_x / std::abs(x2) < relative_epsilon);
}

const bool
is_definitely_less(const double x1, const double x2)
{
    const double delta_x = x1 - x2;
    return delta_x <= -absolute_epsilon &&
           (delta_x / std::abs(x1) <= -relative_epsilon ||
            delta_x / std::abs(x2) <= -relative_epsilon);
}

const double
lerp(const double x1, const double x2, const double t)
{
    return (1 - t) * x1 + t * x2;
}

const std::int64_t
to_fixed(const double x)
{
    return std::round(x * (1ull << fractional_bits));
}

const double
to_float(const std::int64_t x)
{
    return static_cast<double>(x) / (1ull << fractional_bits);
}

} // namespace Geometry
