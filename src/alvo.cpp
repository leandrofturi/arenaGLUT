#include "../include/alvo.h"
#include <cstdio>
#include <math.h>

void Alvo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
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

void Alvo::DesenhaAlvo(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    DesenhaCirc(radiusAlvo, gColor == 0, gColor == 1, gColor == 2);
    glPopMatrix();
}

void Alvo::Recria(GLfloat x, GLfloat y)
{
    gX = x;
    gY = y;
    gColor = (gColor + 1) % 3;
}

bool Alvo::Atingido(Tiro *tiro)
{
    float tX, tY;
    tiro->GetPos(tX, tY);
    return sqrtf((gX - tX) * (gX - tX) + (gY - gY) * (gY - gY)) < radiusAlvo;
}
