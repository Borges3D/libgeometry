#ifndef GEOMETRY_EDGE_H
#define GEOMETRY_EDGE_H

#include <cstddef>

namespace Geometry {

class Edge {
public:
    Edge(const std::size_t a, const std::size_t b);
    const std::size_t& a() const;
    const std::size_t& b() const;

private:
    const std::size_t a_;
    const std::size_t b_;
};

} // namespace Geometry

#endif // GEOMETRY_EDGE_H
