#ifndef GEOMETRY_SIMPLE_POLYGON_NODE_VISITOR_H
#define GEOMETRY_SIMPLE_POLYGON_NODE_VISITOR_H

namespace Geometry {

class Simple_polygon_node;

class Simple_polygon_node_visitor {
public:
    virtual ~Simple_polygon_node_visitor() = default;
    virtual void visit(const Simple_polygon_node& node) = 0;
};

} // namespace Geometry

#endif // GEOMETRY_SIMPLE_POLYGON_NODE_VISITOR_H
