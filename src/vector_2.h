#ifndef GEOMETRY_VECTOR_2_H
#define GEOMETRY_VECTOR_2_H

namespace Geometry {

class Vector_2 {
public:
    Vector_2(const double x, const double y);
    const double& x() const;
    const double& y() const;

private:
    const double x_;
    const double y_;
};

const double dot_product(const Vector_2& v1, const Vector_2& v2);
const double length(const Vector_2& v);
const double squared_length(const Vector_2& v);

} // namespace Geometry

#endif // GEOMETRY_VECTOR_2_H
