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

// https://www.geeksforgeeks.org/check-if-any-point-overlaps-the-given-circle-and-rectangle/
/*
Given two opposite diagonal points of a rectangle (X1, Y1), (X2, Y2) and the center, 
    radius of the circle R, (Xc, Yc), the task is to check if there exists any point P 
    that belongs to both the circle as well as the rectangle.
*/
bool Geometries::intersects(GLfloat R, GLfloat Xc, GLfloat Yc,
                            GLfloat X1, GLfloat Y1,
                            GLfloat X2, GLfloat Y2)
{

    // Find the nearest point on the
    // rectangle to the center of
    // the circle
    GLfloat Xn = fmax(X1, fmin(Xc, X2));
    GLfloat Yn = fmax(Y1, fmin(Yc, Y2));

    // Find the distance between the
    // nearest point and the center
    // of the circle
    // Distance between 2 points,
    // (x1, y1) & (x2, y2) in
    // 2D Euclidean space is
    // ((x1-x2)**2 + (y1-y2)**2)**0.5
    GLfloat Dx = Xn - Xc;
    GLfloat Dy = Yn - Yc;
    return (Dx * Dx + Dy * Dy) <= R * R;
}

// https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
bool Geometries::intersects(GLfloat Aleft, GLfloat Aright, GLfloat Atop, GLfloat Abottom, GLfloat Bleft, GLfloat Bright, GLfloat Btop, GLfloat Bbottom)
{
    return fmax(Aleft, Bleft) < fmin(Aright, Bright) & fmax(Atop, Btop) < fmin(Abottom, Bbottom);
}
