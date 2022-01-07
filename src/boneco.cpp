#include "../include/boneco.h"
#include <math.h>

void Boneco::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    GLfloat halfWidth = width*0.5;

    /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
    glColor3f(R, G, B);
    /* Desenhar um polígono branco (retângulo) */
    glBegin(GL_POLYGON);
        glVertex3f(-halfWidth, 0.0, 0.0);
        glVertex3f(+halfWidth, 0.0, 0.0);
        glVertex3f(+halfWidth, height, 0.0);
        glVertex3f(-halfWidth, height, 0.0);
    glEnd();
}

void Boneco::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    int num_segments = 18;

    glPointSize(5.0);
    glColor3f(R, G, B);
    glBegin(GL_POINTS);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0*M_PI * float(ii) / float(num_segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta); 
        glVertex3f(x, y, 0.0); 
    }
    glEnd();
}

void Boneco::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

        glTranslatef(x, y, 0.0);
        glRotatef(thetaWheel, 0.0, 0.0, 1.0);
        DesenhaCirc(radiusWheel, R, G, B);

    glPopMatrix();
}

void Boneco::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();

        glTranslatef(x, y, 0.0);
        glRotatef(theta1, 0.0, 0.0, 1.0);
        DesenhaRect(paddleHeight, paddleWidth, 0.0, 0.0, 1.0);

        glTranslatef(0.0, paddleHeight, 0.0);
        glRotatef(theta2, 0.0, 0.0, 1.0);
        DesenhaRect(paddleHeight, paddleWidth, 0.0, 1.0, 1.0);

        glTranslatef(0.0, paddleHeight, 0.0);
        glRotatef(theta3, 0.0, 0.0, 1.0);
        DesenhaRect(paddleHeight, paddleWidth, 0.0, 1.0, 0.0);

    glPopMatrix();
}

void Boneco::DesenhaBoneco(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    GLfloat halfWidth = baseWidth*0.5;

    glPushMatrix();

        glTranslatef(x, y, 0.0);
        DesenhaRect(baseHeight, baseWidth, 1.0, 0.0, 0.0);
        DesenhaBraco(0.0, baseHeight, theta1, theta2, theta3);
        DesenhaRoda(-halfWidth, 0.0, thetaWheel, 1.0, 1.0, 1.0);
        DesenhaRoda(+halfWidth, 0.0, thetaWheel, 1.0, 1.0, 1.0);

    glPopMatrix();
}

void Boneco::RodaBraco1(GLfloat inc)
{
    gTheta1 = gTheta1 + inc;
}

void Boneco::RodaBraco2(GLfloat inc)
{
    gTheta2 = gTheta2 + inc;
}

void Boneco::RodaBraco3(GLfloat inc)
{
    gTheta3 = gTheta3 + inc;
}

void Boneco::MoveEmX(GLfloat dx)
{
    gX = gX + 10*dx;
    gThetaWheel = gThetaWheel - 10*(dx*360)/(2.0*M_PI*radiusWheel);
}

void MovePoint(GLfloat &x, GLfloat &y, GLfloat angle, GLfloat step)
{
    float theta = angle*0.0174533;
    x += step*cos(theta);
    y += step*sin(theta);
}

Tiro *Boneco::Atira()
{
    GLfloat posTiroX = gX, posTiroY = gY+baseHeight;
    GLfloat directionAng = gTheta1 + 90;
    MovePoint(posTiroX, posTiroY, directionAng, paddleHeight);
    directionAng += gTheta2;
    MovePoint(posTiroX, posTiroY, directionAng, paddleHeight);
    directionAng += gTheta3;
    MovePoint(posTiroX, posTiroY, directionAng, paddleHeight);

    Tiro *tiro = new Tiro(posTiroX, posTiroY, directionAng);
    return tiro;
}
