#ifndef GEOMETRY_CLIP_OPTIONS_H
#define GEOMETRY_CLIP_OPTIONS_H

#include "clip_type.h"

namespace Geometry {

struct Clip_options {
    Clip_options(Clip_type clip_type);

    Clip_type clip_type;
    double smoothness = 0.9;
    double tolerance = 1E-2;
};

} // namespace Geometry

#endif // GEOMETRY_CLIP_OPTIONS_H
