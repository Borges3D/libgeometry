#ifndef GEOMETRY_RECTANGLE_H
#define GEOMETRY_RECTANGLE_H

#include "point_2.h"
#include "vector_2.h"
#include <memory>

namespace Geometry {

class Simple_polygon;

class Rectangle {
public:
    Rectangle(const Point_2& position, const Vector_2& size);
    const Point_2& position() const;
    const Vector_2& size() const;

private:
    const Point_2 position_;
    const Vector_2 size_;
};

std::shared_ptr<const Simple_polygon> to_simple_polygon(const Rectangle& r);

} // namespace Geometry

#endif // GEOMETRY_RECTANGLE_H
