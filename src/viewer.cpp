#include "geometry.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

using namespace Geometry;

namespace {

void
draw(const Polygon_2& ps)
{
    glBegin(GL_LINE_LOOP);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        glVertex2f(p.x(), p.y());
    }
    glEnd();
}

void
draw(const Polyline_2& ps)
{
    glBegin(GL_LINE_STRIP);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_2& p = ps[index];
        glVertex2f(p.x(), p.y());
    }
    glEnd();
}

void
draw(const Closed_curve_2& c)
{
    draw(*c.to_polygon_2(1E-3));
}

void
draw(const Open_curve_2& c)
{
    draw(*c.to_polyline_2(1E-3));
}

void
draw(const Circle_2& c)
{
    draw(*Curve::create(c));
}

void
draw(const Rectangle_2& r)
{
    draw(*Curve::create(r));
}

void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    std::shared_ptr<const Open_curve_2> curve_1 = Curve_2::fit_open(
        3, {Point_2(-0.75, -0.5), Point_2(0.5, 0.5), Point_2(0.0, 0.75)});
    std::shared_ptr<const Open_curve_2> curve_2 = Curve_2::create(
        *Polyline_2::create({Point_2(+0.5, -0.5), Point_2(-0.5, +0.5)}));
    std::vector<std::shared_ptr<const Polygon_2>> pss1 =
        offset(*curve_1->to_polyline_2(1E-3), 0.1);
    std::vector<std::shared_ptr<const Polygon_2>> pss2 =
        offset(*curve_2->to_polyline_2(1E-3), 0.1);
    std::vector<std::reference_wrapper<const Polygon_2>> ps_refs_1;
    for (const std::shared_ptr<const Polygon_2> ps : pss1) {
        ps_refs_1.push_back(*ps);
    }
    std::vector<std::reference_wrapper<const Polygon_2>> ps_refs_2;
    for (const std::shared_ptr<const Polygon_2> ps : pss2) {
        ps_refs_2.push_back(*ps);
    }
    for (const std::shared_ptr<const Polygon_2>& ps :
         clip(Clip_type::Union, ps_refs_1, ps_refs_2)) {
        draw(*Curve::create(*ps));
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
