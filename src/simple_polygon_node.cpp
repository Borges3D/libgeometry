#include "simple_polygon_node.h"
#include "clipper_utilities.h"
#include "edge.h"
#include "mesh_2.h"
#include "simple_polygon.h"
#include "simple_polygon_node_visitor.h"
#include <cassert>
#include <utility>

namespace Geometry {

namespace {

class Triangulate_visitor : public Simple_polygon_node_visitor {
public:
    Triangulate_visitor(std::vector<Point_2>& vs, std::vector<Edge>& es,
                        std::vector<Point_2>& hs)
        : vs_(vs), es_(es), hs_(hs)
    {
    }

    void
    visit(const Simple_polygon_node& node)
    {
        const Simple_polygon& ps = *node.polygon();
        const std::size_t base = vs_.size();
        for (std::size_t index = 0; index < ps.size(); ++index) {
            vs_.push_back(ps[index]);
        }
        for (std::size_t index = 0; index < ps.size(); ++index) {
            es_.push_back(Edge(base + index, base + (index + 1) % ps.size()));
        }
        if (node.is_hole()) {
            hs_.push_back(get_internal_point(ps));
        }
    }

private:
    std::vector<Point_2>& vs_;
    std::vector<Edge>& es_;
    std::vector<Point_2>& hs_;
};

} // namespace

std::unique_ptr<const Simple_polygon_node>
Simple_polygon_node::create(
    const bool is_hole, std::shared_ptr<const Simple_polygon> polygon,
    std::vector<std::unique_ptr<const Simple_polygon_node>> children)
{
    return std::unique_ptr<const Simple_polygon_node>(new Simple_polygon_node(
        is_hole, std::move(polygon), std::move(children)));
}

const bool&
Simple_polygon_node::is_hole() const
{
    return is_hole_;
}

const std::shared_ptr<const Simple_polygon>&
Simple_polygon_node::polygon() const
{
    return polygon_;
}

const std::size_t
Simple_polygon_node::children_size() const
{
    return children_.size();
}

const Simple_polygon_node&
Simple_polygon_node::child(const std::size_t index) const
{
    assert(index < children_.size());
    return *children_[index];
}

Simple_polygon_node::Simple_polygon_node(
    const bool is_hole, std::shared_ptr<const Simple_polygon> polygon,
    std::vector<std::unique_ptr<const Simple_polygon_node>> children)
    : is_hole_(is_hole), polygon_(std::move(polygon)),
      children_(std::move(children))
{
}

std::unique_ptr<const Simple_polygon_node>
to_simple_polygon_tree(
    const std::vector<std::reference_wrapper<const Polygon_2>>& pss)
{
    ClipperLib::Clipper clipper;
    clipper.StrictlySimple(true);
    for (const Polygon_2& ps : pss) {
        clipper.AddPath(Internal::to_path(ps), ClipperLib::ptSubject, true);
    }
    ClipperLib::PolyTree tree;
    clipper.Execute(ClipperLib::ctUnion, tree, ClipperLib::pftNonZero,
                    ClipperLib::pftNonZero);
    return Internal::to_simple_polygon_tree(tree);
}

std::shared_ptr<const Mesh_2>
triangulate(const Simple_polygon_node& node)
{
    std::vector<Point_2> vs;
    std::vector<Edge> es;
    std::vector<Point_2> hs;
    Triangulate_visitor visitor(vs, es, hs);
    traverse(node, visitor);
    return triangulate(vs, es, hs);
}

void
traverse(const Simple_polygon_node& node, Simple_polygon_node_visitor& visitor)
{
    for (std::size_t index = 0; index < node.children_size(); ++index) {
        const Simple_polygon_node& child = node.child(index);
        visitor.visit(child);
        traverse(child, visitor);
    }
}

} // namespace Geometry
