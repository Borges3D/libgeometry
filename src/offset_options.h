#ifndef GEOMETRY_OFFSET_OPTIONS_H
#define GEOMETRY_OFFSET_OPTIONS_H

#include "cap_type.h"
#include "join_type.h"

namespace Geometry {

struct Offset_options {
    Offset_options(double distance);

    double distance;
    Cap_type cap_type = Cap_type::round;
    Join_type join_type = Join_type::round;
    double miter_limit = 2.0;
    double smoothness = 0.9;
    double tolerance = 1E-2;
};

} // namespace Geometry

#endif // GEOMETRY_OFFSET_OPTIONS_H
