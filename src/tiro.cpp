#include "../include/tiro.h"
#include <math.h>
#include <stdlib.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
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

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
    glPushMatrix();

        glTranslatef(x, y, 0.0);
        DesenhaCirc(radiusTiro, rand() % 255, rand() % 255, rand() % 255);

    glPopMatrix();
}

void Tiro::Move(GLfloat timeDiference)
{
    gX = gX + cos(gDirectionAng*0.0174533)*gVel*timeDiference;
    gY = gY + sin(gDirectionAng*0.0174533)*gVel*timeDiference;
}

bool Tiro::Valido()
{
    return fmax(fabs(gX - gXInit), fabs(gY - gYInit)) < DISTANCIA_MAX;
}
