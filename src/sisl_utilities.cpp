#include "sisl_utilities.h"
#include "unique_malloc_ptr.h"
#include "point_2.h"
#include "point_3.h"
#include <cassert>
#include <cstdlib>

namespace Geometry {

namespace Internal {

Unique_sisl_curve_ptr
fit(const int iopen, const int ik, const std::vector<Point_2>& ps)
{
    std::vector<double> epoint;
    epoint.reserve(ps.size() * 2);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        epoint.push_back(p.x());
        epoint.push_back(p.y());
    }
    std::vector<int> nptyp;
    nptyp.reserve(ps.size());
    for (std::size_t index = 0; index < ps.size(); ++index) {
        nptyp.push_back(1);
    }
    double* epoint_ptr = epoint.data();
    const int inbpnt = ps.size();
    constexpr int idim = 2;
    int* nptyp_ptr = nptyp.data();
    constexpr int icnsta = 0;
    constexpr int icnend = 0;
    const double astpar = 0.0;
    double cendpar = 0.0;
    SISLCurve* rc_ptr = nullptr;
    double* gpar_ptr = nullptr;
    int jnbpar = 0;
    int jstat = 0;
    s1356(epoint_ptr, inbpnt, idim, nptyp_ptr, icnsta, icnend, iopen, ik,
          astpar, &cendpar, &rc_ptr, &gpar_ptr, &jnbpar, &jstat);
    if (jstat < 0) {
        throw std::runtime_error("");
    }
    Unique_sisl_curve_ptr rc(rc_ptr);
    Unique_malloc_ptr<double> gpar(gpar_ptr);
    return rc;
}

Unique_sisl_curve_ptr
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
    std::vector<int> nptyp;
    nptyp.reserve(ps.size());
    for (std::size_t index = 0; index < ps.size(); ++index) {
        nptyp.push_back(1);
    }
    double* epoint_ptr = epoint.data();
    const int inbpnt = ps.size();
    constexpr int idim = 3;
    int* nptyp_ptr = nptyp.data();
    constexpr int icnsta = 0;
    constexpr int icnend = 0;
    const double astpar = 0.0;
    double cendpar = 0.0;
    SISLCurve* rc_ptr = nullptr;
    double* gpar_ptr = nullptr;
    int jnbpar = 0;
    int jstat = 0;
    s1356(epoint_ptr, inbpnt, idim, nptyp_ptr, icnsta, icnend, iopen, ik,
          astpar, &cendpar, &rc_ptr, &gpar_ptr, &jnbpar, &jstat);
    if (jstat < 0) {
        throw std::runtime_error("");
    }
    Unique_sisl_curve_ptr rc(rc_ptr);
    Unique_malloc_ptr<double> gpar(gpar_ptr);
    return rc;
}

std::tuple<Unique_sisl_curve_ptr, Unique_sisl_curve_ptr>
split(SISLCurve* pc1_ptr, const double apar)
{
    SISLCurve* rcnew1_ptr = nullptr;
    SISLCurve* rcnew2_ptr = nullptr;
    int jstat = 0;
    s1710(pc1_ptr, apar, &rcnew1_ptr, &rcnew2_ptr, &jstat);
    if (jstat < 0) {
        throw std::runtime_error("");
    }
    Unique_sisl_curve_ptr rcnew1(rcnew1_ptr);
    Unique_sisl_curve_ptr rcnew2(rcnew2_ptr);
    if (jstat == 2) {
        pc1_ptr = rcnew1.get();
        rcnew1_ptr = nullptr;
        rcnew2_ptr = nullptr;
        jstat = 0;
        s1710(pc1_ptr, apar, &rcnew1_ptr, &rcnew2_ptr, &jstat);
        rcnew1.reset(rcnew1_ptr);
        rcnew2.reset(rcnew2_ptr);
    }
    return std::make_tuple(std::move(rcnew1), std::move(rcnew2));
}

} // namespace Internal

} // namespace Geometry
