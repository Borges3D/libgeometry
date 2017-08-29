#include "sisl_utilities.h"
#include "point_2.h"
#include <cassert>

namespace Geometry {

const std::vector<Point_2>
to_points(bool is_closed, const std::size_t size, const double* points)
{
    std::vector<Point_2> ps;
    ps.push_back(Point_2(points[0], points[1]));
    for (std::size_t index = 1; index < size; ++index) {
        const std::size_t base = index * 2;
        Point_2 p(points[base + 0], points[base + 1]);
        if (!is_approximately_equal(p, ps.back())) {
            ps.push_back(p);
        }
    }
    if (is_closed) {
        assert(is_approximately_equal(ps.front(), ps.back()));
        ps.pop_back();
    }
    return ps;
}

} // namespace Geometry
