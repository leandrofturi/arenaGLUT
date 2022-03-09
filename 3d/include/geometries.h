#ifndef GEOMETRIES_H
#define GEOMETRIES_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct
{
    //Vertex coordinate
    double X;
    double Y;
    double Z;

    //Vertex normal
    double nX;
    double nY;
    double nZ;

    //Vertex texture coordinate
    double U;
    double V;
} VERTICES;

typedef struct
{
    VERTICES *vtx;
    int numVtx;
    double radius;
} OBJ;

typedef struct
{
    double R;
    double G;
    double B;
} COLOR;

namespace Geometries
{
    OBJ *CreateSphere(double R, double space);
    OBJ *CreateBody(double width, double height, double depth, COLOR color);
    void CreateSolidCube(double width, double height, double depth, COLOR color);
    void CreateSolidSphere(double radius, COLOR color);
    void drawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
    float toRad(float theta);
}
#endif /* GEOMETRIES_H */
