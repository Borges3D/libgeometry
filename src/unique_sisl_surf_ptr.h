#ifndef UNIQUE_SISL_SURF_PTR_H
#define UNIQUE_SISL_SURF_PTR_H

#include <sisl.h>
#include <memory>

namespace Geometry {

namespace Internal {

struct Free_surf_deleter {
    void operator()(SISLSurf* surf);
};

using Unique_sisl_surf_ptr = std::unique_ptr<SISLSurf, Free_surf_deleter>;

} // namespace Internal

} // namespace Geometry

#endif // UNIQUE_SISL_SURF_PTR_H
