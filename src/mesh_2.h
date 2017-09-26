#ifndef GEOMETRY_MESH_2_H
#define GEOMETRY_MESH_2_H

#include "face.h"
#include "point_2.h"
#include <memory>
#include <vector>

namespace Geometry {

class Edge;

class Mesh_2 {
public:
    static std::shared_ptr<const Mesh_2> create(std::vector<Point_2> vertices,
                                                std::vector<Face> faces);
    const std::size_t vertices_size() const;
    const Point_2& vertex(const std::size_t index) const;
    const std::size_t faces_size() const;
    const Face& face(const std::size_t index) const;

private:
    Mesh_2(std::vector<Point_2> vertices, std::vector<Face> faces);

    const std::vector<Point_2> vertices_;
    const std::vector<Face> faces_;
};

std::shared_ptr<const Mesh_2> triangulate(const std::vector<Point_2>& vs,
                                          const std::vector<Edge>& es,
                                          const std::vector<Point_2>& hs);

} // namespace Geometry

#endif // GEOMETRY_MESH_2_H
