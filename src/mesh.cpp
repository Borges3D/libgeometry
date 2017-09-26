#include "mesh.h"
#include <cassert>
#include <utility>

namespace Geometry {

const std::size_t
Mesh::faces_size() const
{
    return faces_.size();
}

const Face&
Mesh::face(const std::size_t index) const
{
    assert(index < faces_.size());
    return faces_[index];
}

Mesh::Mesh(std::vector<Face> faces) : faces_(std::move(faces))
{
}

} // namespace Geometry
