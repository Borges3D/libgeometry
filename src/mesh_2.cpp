#include "mesh_2.h"
#include "edge.h"
#include "unique_malloc_ptr.h"
#include <cassert>
#include <utility>
#ifdef ANSI_DECLARATORS
#define GEOMETRY_ANSI_DECLARATORS
#undef ANSI_DECLARATORS
#endif // ANSI_DECLARATORS
#ifdef REAL
#define GEOMETRY_REAL REAL
#undef REAL
#endif // REAL
#ifdef VOID
#define GEOMETRY_VOID VOID
#undef VOID
#endif
#define ANSI_DECLARATORS
#define REAL double
#define VOID void
extern "C" {
#include <triangle.h>
} // extern "C"
#undef VOID
#undef REAL
#undef ANSI_DECLARATORS
#ifdef GEOMETRY_VOID
#define VOID GEOMETRY_VOID
#undef GEOMETRY_VOID
#endif // GEOMETRY_VOID
#ifdef GEOMETRY_REAL
#define REAL GEOMETRY_REAL
#undef GEOMETRY_REAL
#endif // GEOMETRY_REAL
#ifdef GEOMETRY_ANSI_DECLARATORS
#define ANSI_DECLARATORS GEOMETRY_ANSI_DECLARATORS
#undef ANSI_DECLARATORS
#endif // GEOMETRY_ANSI_DECLARATORS

namespace Geometry {

std::shared_ptr<const Mesh_2>
Mesh_2::create(std::vector<Point_2> vertices, std::vector<Face> faces)
{
    return std::shared_ptr<const Mesh_2>(
        new Mesh_2(std::move(vertices), std::move(faces)));
}

const std::size_t
Mesh_2::vertices_size() const
{
    return vertices_.size();
}

const Point_2&
Mesh_2::vertex(const std::size_t index) const
{
    assert(index < vertices_.size());
    return vertices_[index];
}

const std::size_t
Mesh_2::faces_size() const
{
    return faces_.size();
}

const Face&
Mesh_2::face(const std::size_t index) const
{
    assert(index < faces_.size());
    return faces_[index];
}

Mesh_2::Mesh_2(std::vector<Point_2> vertices, std::vector<Face> faces)
    : vertices_(std::move(vertices)), faces_(std::move(faces))
{
}

std::shared_ptr<const Mesh_2> triangulate(const std::vector<Point_2>& vs,
                                          const std::vector<Edge>& es,
                                          const std::vector<Point_2>& hs)
{
    char triswitches[] = "Qpqz";
    std::vector<double> pointlist_in;
    pointlist_in.reserve(vs.size() * 2);
    for (std::size_t index = 0; index < vs.size(); ++index) {
        const Point_2& vertex = vs[index];
        pointlist_in.push_back(vertex.x());
        pointlist_in.push_back(vertex.y());
    }
    std::vector<int> segmentlist_in;
    segmentlist_in.reserve(es.size() * 2);
    for (std::size_t index = 0; index < es.size(); ++index) {
        const Edge& edge = es[index];
        segmentlist_in.push_back(edge.a());
        segmentlist_in.push_back(edge.b());
    }
    std::vector<double> holelist_in;
    holelist_in.reserve(hs.size() * 2);
    for (std::size_t index = 0; index < hs.size(); ++index) {
        const Point_2& hole = hs[index];
        holelist_in.push_back(hole.x());
        holelist_in.push_back(hole.y());
    }
    triangulateio in;
    in.pointlist = pointlist_in.data();
    in.pointattributelist = nullptr;
    in.pointmarkerlist = nullptr;
    in.numberofpoints = vs.size();
    in.numberofpointattributes = 0;
    in.trianglelist = nullptr;
    in.triangleattributelist = nullptr;
    in.trianglearealist = nullptr;
    in.neighborlist = nullptr;
    in.numberoftriangles = 0;
    in.numberofcorners = 0;
    in.numberoftriangleattributes = 0;
    in.segmentlist = segmentlist_in.data();
    in.segmentmarkerlist = nullptr;
    in.numberofsegments = es.size();
    in.holelist = holelist_in.data();
    in.numberofholes = hs.size();
    in.regionlist = nullptr;
    in.numberofregions = 0;
    in.edgelist = nullptr;
    in.edgemarkerlist = nullptr;
    in.normlist = nullptr;
    in.numberofedges = 0;
    triangulateio out;
    out.pointlist = nullptr;
    out.pointattributelist = nullptr;
    out.pointmarkerlist = nullptr;
    out.numberofpoints = 0;
    out.numberofpointattributes = 0;
    out.trianglelist = nullptr;
    out.triangleattributelist = nullptr;
    out.trianglearealist = nullptr;
    out.neighborlist = nullptr;
    out.numberoftriangles = 0;
    out.numberofcorners = 0;
    out.numberoftriangleattributes = 0;
    out.segmentlist = nullptr;
    out.segmentmarkerlist = nullptr;
    out.numberofsegments = 0;
    out.holelist = nullptr;
    out.numberofholes = 0;
    out.regionlist = nullptr;
    out.numberofregions = 0;
    out.edgelist = nullptr;
    out.edgemarkerlist = nullptr;
    out.normlist = nullptr;
    out.numberofedges = 0;
    triangulate(triswitches, &in, &out, nullptr);
    Internal::Unique_malloc_ptr<double> pointlist_out(out.pointlist);
    Internal::Unique_malloc_ptr<int> trianglelist_out(out.trianglelist);
    std::vector<Point_2> vertices;
    const double* pointlist_src = pointlist_out.get();
    for (std::size_t index = 0; index < out.numberofpoints; ++index) {
        const double x = *pointlist_src++;
        const double y = *pointlist_src++;
        vertices.push_back(Point_2(x, y));
    }
    std::vector<Face> faces;
    const int* trianglelist_src = trianglelist_out.get();
    for (std::size_t index = 0; index < out.numberoftriangles; ++index) {
        const double a = *trianglelist_src++;
        const double b = *trianglelist_src++;
        const double c = *trianglelist_src++;
        faces.push_back(Face(a, b, c));
    }
    return Mesh_2::create(vertices, faces);
}

} // namespace Geometry
