#ifndef GEOMETRY_SURFACE_H
#define GEOMETRY_SURFACE_H

#include "unique_sisl_surf_ptr.h~"

namespace Geometry {

class Surface {
private:
    Surface(Internal::Unique_sisl_surfptr surf);

    Internal::Unique_sisl_surf_ptr surf_;
};

} // namespace Geometry

#endif // GEOMETRY_SURFACE_H
