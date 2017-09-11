#include "polyline_3.h"
#include "utilities.h"
#include <cassert>

namespace Geometry {

std::shared_ptr<const Polyline_3>
Polyline_3::create(const std::vector<Point_3> points)
{
    return std::shared_ptr<const Polyline_3>(new Polyline_3(std::move(points)));
}

const std::size_t
Polyline_3::size() const
{
    return points_.size();
}

const Point_3&
Polyline_3::operator[](std::size_t index) const
{
    assert(index < points_.size());
    return points_[index];
}

Polyline_3::Polyline_3(const std::vector<Point_3> points)
    : points_(std::move(points))
{
    assert(points_.size() >= 2);
#ifndef NDEBUG
    for (std::size_t index = 0; index < points.size() - 1; ++index) {
        assert(!is_approximately_equal(points_[index], points[index + 1]));
    }
#endif // !NDEBUG
}

const double
length(const Polyline_3& ps)
{
    double len = 0.0;
    for (std::size_t index = 1; index < ps.size(); ++index) {
        len += distance(ps[index - 1], ps[index]);
    }
    return len;
}

const std::vector<double>
parameters(const Polyline_3& ps)
{
    const double len = length(ps);
    std::vector<double> ts;
    ts.reserve(ps.size());
    double d = 0.0;
    ts.push_back(0.0);
    for (std::size_t index = 1; index < ps.size(); ++index) {
        d += distance(ps[index - 1], ps[index]);
        ts.push_back(d / len);
    }
    return ts;
}

} // namespace Geometry
