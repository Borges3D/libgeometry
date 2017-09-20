#ifndef GEOMETRY_UNIQUE_MALLOC_PTR_H
#define GEOMETRY_UNIQUE_MALLOC_PTR_H

#include <memory>

namespace Geometry {

namespace Internal {

struct Free_deleter {
    void operator()(void* ptr);
};

template <typename T>
using Unique_malloc_ptr = std::unique_ptr<T, Free_deleter>;

} // namespace Internal

} // namespace Geometry

#endif // GEOMETRY_UNIQUE_MALLOC_PTR_H
