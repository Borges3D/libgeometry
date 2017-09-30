#ifndef GEOMETRY_SIMPLE_POLYGON_NODE_H
#define GEOMETRY_SIMPLE_POLYGON_NODE_H

#include <memory>
#include <vector>

namespace Geometry {

class Mesh_2;
class Polygon_2;
class Simple_polygon;
class Simple_polygon_node_visitor;

class Simple_polygon_node {
public:
    static std::unique_ptr<const Simple_polygon_node>
    create(const bool is_hole, std::shared_ptr<const Simple_polygon> polygon,
           std::vector<std::unique_ptr<const Simple_polygon_node>> children);
    const bool& is_hole() const;
    const std::shared_ptr<const Simple_polygon>& polygon() const;
    const std::size_t children_size() const;
    const Simple_polygon_node& child(const std::size_t index) const;

private:
    Simple_polygon_node(
        const bool is_hole, std::shared_ptr<const Simple_polygon> polygon,
        std::vector<std::unique_ptr<const Simple_polygon_node>> children);

    const bool is_hole_;
    std::shared_ptr<const Simple_polygon> polygon_;
    std::vector<std::unique_ptr<const Simple_polygon_node>> children_;
};

std::unique_ptr<const Simple_polygon_node> to_simple_polygon_tree(
    const std::vector<std::reference_wrapper<const Polygon_2>>& pss);
std::shared_ptr<const Mesh_2> triangulate(const Simple_polygon_node& node);
void traverse(const Simple_polygon_node& node,
              Simple_polygon_node_visitor& visitor);

} // namespace Geometry

#endif // GEOMETRY_SIMPLE_POLYGON_NODE_H
