#include "unique_sisl_curve_ptr.h"

namespace Geometry {

namespace Internal {

void
Free_curve_deleter::operator()(SISLCurve* curve)
{
    freeCurve(curve);
}

} // namespace Internal

} // namespace Geometry
