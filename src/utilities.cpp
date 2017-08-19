#include "utilities.h"
#include <cmath>

namespace Geometry {

constexpr int fractional_bits = 32;

std::int64_t
to_fixed(double x)
{
    return std::round(x * (1ull << fractional_bits));
}

double
to_float(std::int64_t x)
{
    return static_cast<double>(x) / (1ull << fractional_bits);
}

} // namespace Geometry
