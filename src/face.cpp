#include "face.h"

namespace Geometry {

Face::Face(const std::size_t a, const std::size_t b, const std::size_t c)
    : a_(a), b_(b), c_(c)
{
}

const std::size_t&
Face::a() const
{
    return a_;
}

const std::size_t&
Face::b() const
{
    return b_;
}

const std::size_t&
Face::c() const
{
    return c_;
}

} // namespace Geometry
