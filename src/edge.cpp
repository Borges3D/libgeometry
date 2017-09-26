#include "edge.h"

namespace Geometry {

Edge::Edge(const std::size_t a, const std::size_t b) : a_(a), b_(b)
{
}

const std::size_t&
Edge::a() const
{
    return a_;
}

const std::size_t&
Edge::b() const
{
    return b_;
}

} // namespace Geometry
