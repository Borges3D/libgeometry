#include "sisl_utilities.h"
#include "point_2.h"
#include "point_3.h"
#include <cassert>
#include <cstdlib>

namespace Geometry {

std::unique_ptr<SISLCurve, decltype(&freeCurve)>
fit(const int iopen, const int ik, const std::vector<Point_2>& ps)
{
    std::vector<double> epoint;
    epoint.reserve(ps.size() * 2);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        epoint.push_back(p.x());
        epoint.push_back(p.y());
    }
    const int inbpnt = ps.size();
    constexpr int idim = 2;
    std::vector<int> nptyp;
    nptyp.reserve(ps.size());
    for (std::size_t index = 0; index < ps.size(); ++index) {
        nptyp.push_back(1);
    }
    constexpr int icnsta = 0;
    constexpr int icnend = 0;
    const double astpar = 0.0;
    double cendpar = 0.0;
    SISLCurve* rc_ = nullptr;
    double* gpar_ = nullptr;
    int jnbpar = 0;
    int jstat = 0;
    s1356(epoint.data(), inbpnt, idim, nptyp.data(), icnsta, icnend, iopen, ik,
          astpar, &cendpar, &rc_, &gpar_, &jnbpar, &jstat);
    if (jstat < 0) {
        throw std::runtime_error("");
    }
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> rc(rc_, &freeCurve);
    std::unique_ptr<double[], decltype(&std::free)> gpar(gpar_, &std::free);
    return rc;
}

std::unique_ptr<SISLCurve, decltype(&freeCurve)>
fit(const int iopen, const int ik, const std::vector<Point_3>& ps)
{
    std::vector<double> epoint;
    epoint.reserve(ps.size() * 3);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_3& p = ps[index];
        epoint.push_back(p.x());
        epoint.push_back(p.y());
        epoint.push_back(p.z());
    }
    const int inbpnt = ps.size();
    constexpr int idim = 3;
    std::vector<int> nptyp;
    nptyp.reserve(ps.size());
    for (std::size_t index = 0; index < ps.size(); ++index) {
        nptyp.push_back(1);
    }
    constexpr int icnsta = 0;
    constexpr int icnend = 0;
    const double astpar = 0.0;
    double cendpar = 0.0;
    SISLCurve* rc_ = nullptr;
    double* gpar_ = nullptr;
    int jnbpar = 0;
    int jstat = 0;
    s1356(epoint.data(), inbpnt, idim, nptyp.data(), icnsta, icnend, iopen, ik,
          astpar, &cendpar, &rc_, &gpar_, &jnbpar, &jstat);
    if (jstat < 0) {
        throw std::runtime_error("");
    }
    std::unique_ptr<SISLCurve, decltype(&freeCurve)> rc(rc_, &freeCurve);
    std::unique_ptr<double[], decltype(&std::free)> gpar(gpar_, &std::free);
    return rc;
}

const std::vector<Point_2>
to_points_2(const bool is_closed, const std::size_t size, const double* points)
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

const std::vector<Point_3>
to_points_3(const bool is_closed, const std::size_t size, const double* points)
{
    std::vector<Point_3> ps;
    ps.push_back(Point_3(points[0], points[1], points[2]));
    for (std::size_t index = 1; index < size; ++index) {
        const std::size_t base = index * 3;
        Point_3 p(points[base + 0], points[base + 1], points[base + 2]);
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
