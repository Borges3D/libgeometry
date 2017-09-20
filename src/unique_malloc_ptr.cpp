#include "unique_malloc_ptr.h"
#include <cstdlib>

namespace Geometry {

namespace Internal {

void
Free_deleter::operator()(void* ptr)
{
    std::free(ptr);
}

} // namespace Internal

} // namespace Geometry
