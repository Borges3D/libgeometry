#include "unique_sisl_surf_ptr.h"

namespace Geometry {

namespace Internal {

void
Free_surf_deleter::operator()(SISLSurf* surf)
{
    freeSurf(surf);
}

} // namespace Internal

} // namespace Geometry
