#include "simple_polygon.h"
#include "clipper_utilities.h"
#include "edge.h"
#include "mesh_2.h"
#include "unique_malloc_ptr.h"

namespace Geometry {

std::shared_ptr<const Simple_polygon>
Simple_polygon::create(const std::vector<Point_2> points)
{
    return std::shared_ptr<const Simple_polygon>(
        new Simple_polygon(std::move(points)));
}

Simple_polygon::Simple_polygon(const std::vector<Point_2> points)
    : Polygon_2(points)
{
}

std::vector<std::shared_ptr<const Simple_polygon>>
simplify(const Polygon_2& ps)
{
    ClipperLib::Paths paths;
    ClipperLib::SimplifyPolygon(Internal::to_path(ps), paths);
    std::vector<std::shared_ptr<const Simple_polygon>> pss;
    for (const ClipperLib::Path& path : paths) {
        pss.push_back(Internal::to_simple_polygon(path));
    }
    return pss;
}

std::shared_ptr<const Mesh_2>
triangulate(const Simple_polygon& ps)
{
    std::vector<Point_2> vs;
    vs.reserve(ps.size());
    for (std::size_t index = 0; index < ps.size(); ++index) {
        vs.push_back(ps[index]);
    }
    std::vector<Edge> es;
    es.reserve(ps.size());
    for (std::size_t index = 0; index < ps.size(); ++index) {
        es.push_back(Edge(index, (index + 1) % ps.size()));
    }
    std::vector<Point_2> hs;
    return triangulate(vs, es, hs);
}

} // namespace Geometry
