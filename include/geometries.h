#ifndef GEOMETRIES_H
#define	GEOMETRIES_H
#include <GL/gl.h>
#include <GL/glu.h>

namespace Geometries {
    float toRad(float theta);
    void drawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
    void drawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
}

#endif	/* GEOMETRIES_H */

