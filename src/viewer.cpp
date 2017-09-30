#include "geometry.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <cstdlib>
#include <iostream>

using namespace Geometry;

namespace {

double angle = 0.0;

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
draw(const Polygon_3& ps)
{
    glBegin(GL_LINE_LOOP);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_3& p = ps[index];
        glVertex3f(p.x(), p.y(), p.z());
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
draw(const Polyline_3& ps)
{
    glBegin(GL_LINE_STRIP);
    for (std::size_t index = 0; index < ps.size(); ++index) {
        const Point_3& p = ps[index];
        glVertex3f(p.x(), p.y(), p.z());
    }
    glEnd();
}

void
draw(const Closed_curve_2& c)
{
    draw(*linearize(c));
}

void
draw(const Open_curve_2& c)
{
    draw(*linearize(c));
}

void
draw(const Curve_2& c)
{
    if (c.is_closed()) {
        draw(c.as_closed_curve_2());
    }
    else {
        draw(c.as_open_curve_2());
    }
}

void
draw(const Closed_curve_3& c)
{
    draw(*linearize(c));
}

void
draw(const Open_curve_3& c)
{
    draw(*linearize(c));
}

void
draw(const Curve_3& c)
{
    if (c.is_closed()) {
        draw(c.as_closed_curve_3());
    }
    else {
        draw(c.as_open_curve_3());
    }
}

void
draw(const Circle& c)
{
    draw(*Closed_curve_2::create(c));
}

void
draw(const Rectangle& r)
{
    draw(*Closed_curve_2::create(r));
}

void
draw(const Mesh_2& m)
{
    for (std::size_t index = 0; index < m.faces_size(); ++index) {
        glBegin(GL_LINE_LOOP);
        const Face& f = m.face(index);
        Point_2 p1 = m.vertex(f.a());
        glVertex2f(p1.x(), p1.y());
        Point_2 p2 = m.vertex(f.b());
        glVertex2f(p2.x(), p2.y());
        Point_2 p3 = m.vertex(f.c());
        glVertex2f(p3.x(), p3.y());
        glEnd();
    }
}

std::shared_ptr<const Open_curve_2> c;

void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glRotated(angle, 5.0, 3.0, 1.0);
    std::vector<std::shared_ptr<const Polygon_2>> pss;
    glColor3f(1.0, 0.0, 0.0);
    draw(*c);
    for (std::shared_ptr<const Closed_curve_2> c : offset(*c, 0.2)) {
        glColor3f(0.0, 1.0, 0.0);
        draw(*c);
        for (std::shared_ptr<const Closed_curve_2> c : offset(*c, 0.1)) {
            glColor3f(0.0, 0.0, 1.0);
            draw(*c);
            pss.push_back(linearize(*c));
        }
    }
    std::vector<std::reference_wrapper<const Polygon_2>> ps_refs;
    for (const std::shared_ptr<const Polygon_2>& ps : pss) {
        ps_refs.push_back(*ps);
    }
    glColor3f(0.5, 0.5, 0.5);
    draw(*triangulate(*to_simple_polygon_tree(ps_refs)));
    glutSwapBuffers();
}

void
generate(void)
{
    c = nullptr;
    do {
        std::vector<Point_2> ps;
        for (std::size_t i = 0; i < 10; ++i) {
            ps.push_back(Point_2(1.5 * (random() % 100) / 100 - 0.75,
                                 1.5 * (random() % 100) / 100 - 0.75));
        }
        try {
            c = Open_curve_2::fit(3, ps);
        }
        catch (...) {}
    }
    while (!c);
}

void
idle(void)
{
    generate();
    glutPostRedisplay();
}

void
keyboard(unsigned char key, int x, int y)
{
    generate();
    glutPostRedisplay();
}

void
reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glutPostRedisplay();
}

void
timer(int value)
{
    angle += 1.0;
    glutPostRedisplay();
    glutTimerFunc(1000.0 / 30.0, timer, 0);
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
    // glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000.0 / 30.0, timer, 0);
    generate();
    glutMainLoop();
    return 0;
}
