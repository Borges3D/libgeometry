#ifndef GEOMETRY_MESH_H
#define GEOMETRY_MESH_H

#include "face.h"
#include <vector>

namespace Geometry {

class Mesh {
public:
    const std::size_t faces_size() const;
    const Face& face(const std::size_t index) const;
    virtual const std::size_t vertices_size() const = 0;

protected:
    Mesh(std::vector<Face> faces);

    const std::vector<Face> faces_;
};

} // namespace Geometry

#endif // GEOMETRY_MESH_H
