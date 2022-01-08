#include "../include/geometries.h"
#include <math.h>

float Geometries::toRad(float theta)
{
    return theta * 0.0174533;
}

void Geometries::drawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
    GLfloat halfWidth = width * 0.5;

    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glVertex3f(-halfWidth, 0.0, 0.0);
    glVertex3f(+halfWidth, 0.0, 0.0);
    glVertex3f(+halfWidth, height, 0.0);
    glVertex3f(-halfWidth, height, 0.0);
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