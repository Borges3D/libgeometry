#include "geometry.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

using namespace Geometry;

namespace {

void
draw(const Polygon_2& polygon)
{
    glBegin(GL_LINE_LOOP);
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        const Point_2& point = polygon.point(index);
        glVertex2f(point.x(), point.y());
    }
    glEnd();
}

void
draw(const Polyline_2& polyline)
{
    glBegin(GL_LINE_STRIP);
    for (std::size_t index = 0; index < polyline.size(); ++index) {
        const Point_2& point = polyline.point(index);
        glVertex2f(point.x(), point.y());
    }
    glEnd();
}

void
draw(const Closed_curve_2& curve)
{
    draw(*curve.to_polygon_2(1E-3));
}

void
draw(const Open_curve_2& curve)
{
    draw(*curve.to_polyline_2(1E-3));
}

void
draw(const Circle_2& circle)
{
    draw(*Curve::create(circle));
}

void
draw(const Rectangle_2& rectangle)
{
    draw(*Curve::create(rectangle));
}

void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    std::vector<std::shared_ptr<const Polygon_2>> polygons_1 =
        offset(*Curve_2::create(*Polyline_2::create(
                                    {Point_2(-0.5, -0.5), Point_2(+0.5, +0.5)}))
                    ->to_polyline_2(1E-3),
               0.25);
    std::vector<std::shared_ptr<const Polygon_2>> polygons_2 =
        offset(*Curve_2::create(*Polyline_2::create(
                                    {Point_2(+0.5, -0.5), Point_2(-0.5, +0.5)}))
                    ->to_polyline_2(1E-3),
               0.25);
    std::vector<std::reference_wrapper<const Polygon_2>> polygon_refs_1;
    for (const std::shared_ptr<const Polygon_2> polygon : polygons_1) {
        polygon_refs_1.push_back(*polygon);
    }
    std::vector<std::reference_wrapper<const Polygon_2>> polygon_refs_2;
    for (const std::shared_ptr<const Polygon_2> polygon : polygons_2) {
        polygon_refs_2.push_back(*polygon);
    }
    for (const std::shared_ptr<const Polygon_2>& polygon :
         clip(Clip_type::Union, polygon_refs_1, polygon_refs_2)) {
        draw(*polygon);
    }
    glutSwapBuffers();
}

void
reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glutPostRedisplay();
}

} // namespace

int
main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
