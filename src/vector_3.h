#ifndef GEOMETRY_VECTOR_3_H
#define GEOMETRY_VECTOR_3_H

namespace Geometry {

class Vector_3 {
public:
    Vector_3(const double x, const double y, const double z);
    const double& x() const;
    const double& y() const;
    const double& z() const;

private:
    const double x_;
    const double y_;
    const double z_;
};

const Vector_3 cross_product(const Vector_3& v1, const Vector_3& v2);
const double dot_product(const Vector_3& v1, const Vector_3& v2);
const bool is_approximately_equal(const Vector_3& v1, const Vector_3& v2);
const bool is_definitely_less(const Vector_3& v1, const Vector_3& v2);
const double length(const Vector_3& v);
const Vector_3 lerp(const Vector_3& v1, const Vector_3& v2, const double t);
const Vector_3 normalize(const Vector_3& v);
const Vector_3 operator+(const Vector_3& v);
const Vector_3 operator+(const Vector_3& v1, const Vector_3& v2);
const Vector_3 operator-(const Vector_3& v);
const Vector_3 operator-(const Vector_3& v1, const Vector_3& v2);
const Vector_3 operator*(const Vector_3& v, const double c);
const Vector_3 operator*(const double c, const Vector_3& v);
const Vector_3 operator/(const Vector_3& v, const double c);
const double squared_length(const Vector_3& v);

} // namespace Geometry

#endif // GEOMETRY_VECTOR_#_H
