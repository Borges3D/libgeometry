#include "geometry.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <cstdlib>

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
    draw(*c.to_polygon_2());
}

void
draw(const Open_curve_2& c)
{
    draw(*c.to_polyline_2());
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
    draw(*c.to_polygon_3());
}

void
draw(const Open_curve_3& c)
{
    draw(*c.to_polyline_3());
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
draw(const Circle_2& c)
{
    draw(*Closed_curve_2::create(c));
}

void
draw(const Rectangle_2& r)
{
    draw(*Closed_curve_2::create(r));
}

std::shared_ptr<const Open_curve_2> c;

void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    draw(*c);
    for (std::shared_ptr<const Closed_curve_2> c : offset(*c, 0.2)) {
        glColor3f(0.0, 1.0, 0.0);
        draw(*c);
        for (std::shared_ptr<const Closed_curve_2> c : offset(*c, 0.1)) {
            std::tuple<std::shared_ptr<const Open_curve_2>,
                       std::shared_ptr<const Open_curve_2>>
                c1c2 = c->split(c->u_min())->split((c->u_min() + c->u_max()) / 2.0);
            glColor3f(0.0, 0.0, 1.0);
            draw(*std::get<0>(c1c2));
            glColor3f(1.0, 0.0, 1.0);
            draw(*std::get<1>(c1c2));
        }
    }
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
    generate();
    glutMainLoop();
    return 0;
}
