#include "../include/geometries.h"
#include <math.h>

float Geometries::toRad(float theta)
{
    return theta * 0.0174533;
}

void Geometries::drawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(width, 0.0, 0.0);
    glVertex3f(width, height, 0.0);
    glVertex3f(0.0, height, 0.0);
    glEnd();
}

void Geometries::drawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    int num_segments = 30;

    glPointSize(5.0);
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0 * M_PI * float(ii) / float(num_segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex3f(x, y, 0.0);
    }
    glEnd();
}

void Geometries::movePoint(GLfloat &x, GLfloat &y, GLfloat angle, GLfloat step)
{
    float theta = toRad(angle);
    x += step * cos(theta);
    y += step * sin(theta);
}

void Geometries::rotatePoint(GLfloat cx, GLfloat cy, GLfloat angle, GLfloat &x, GLfloat &y)
{
    GLfloat s = sin(angle);
    GLfloat c = cos(angle);

    // translate point back to origin:
    x -= cx;
    y -= cy;

    // rotate point
    GLfloat xnew = x * c - y * s;
    GLfloat ynew = x * s + y * c;

    // translate point back:
    x = xnew + cx;
    y = ynew + cy;
}