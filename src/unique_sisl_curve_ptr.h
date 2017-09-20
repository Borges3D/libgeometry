#ifndef UNIQUE_SISL_CURVE_PTR_H
#define UNIQUE_SISL_CURVE_PTR_H

#include <sisl.h>
#include <memory>

namespace Geometry {

namespace Internal {

struct Free_curve_deleter {
    void operator()(SISLCurve* curve);
};

using Unique_sisl_curve_ptr = std::unique_ptr<SISLCurve, Free_curve_deleter>;

} // namespace Internal

} // namespace Geometry

#endif // UNIQUE_SISL_CURVE_PTR_H
