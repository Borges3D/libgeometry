#include "utilities.h"
#include <cmath>

namespace Geometry {

namespace {

constexpr int fractional_bits = 32;
constexpr double relative_epsilon = 1E-6;

} // namespace

const bool
is_approximately_equal(const double x1, const double x2)
{
    const double d = std::abs(x2 - x1);
    if (d < absolute_epsilon) {
        return true;
    }
    const double d1 = std::abs(x1);
    const double d2 = std::abs(x2);
    if (d1 < d2) {
        return std::abs(d1) / d < relative_epsilon;
    }
    else {
        return std::abs(d2) / d < relative_epsilon;
    }
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
