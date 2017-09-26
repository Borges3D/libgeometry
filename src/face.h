#ifndef GEOMETRY_FACE_H
#define GEOMETRY_FACE_H

#include <cstddef>

namespace Geometry {

class Face {
public:
    Face(const std::size_t a, const std::size_t b, const std::size_t c);
    const std::size_t& a() const;
    const std::size_t& b() const;
    const std::size_t& c() const;

private:
    const std::size_t a_;
    const std::size_t b_;
    const std::size_t c_;
};

} // namespace Geometry

#endif // GEOMETRY_FACE_H
