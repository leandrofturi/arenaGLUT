#include "../include/block.h"
#include "../include/geometries.h"
#include "../include/rawLoader.h"
#include "../include/shapes.h"

void Block::draw()
{
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-gX, gY, -gZ);
    Geometries::CreateSolidCube(gWidth, gHeight, gDepth, COLOR{0.16, 0.11, 0.07});
    glPopMatrix();
    glPopAttrib();

    //
    glDepthMask(GL_FALSE);
    glPushMatrix();
    glTranslatef(-gX, gY + gHeight / 2.0, -gZ);
    glCallList(displayList);
    glPopMatrix();
    glDepthMask(GL_TRUE);
}

// Initialise by loading textures etc.
void Block::init()
{
    //load textures
    RawLoader rawLoader;
    Shapes shapes;

    floorTexture = rawLoader.LoadTextureRAW("img/terraintexture.raw", 0, 1024, 1024);

    // load the skybox to a display list
    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);

    GLfloat terraincolour[4] = {0.16f, 0.11f, 0.07f, 1.0f};

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, terraincolour); // material colour
    glBindTexture(GL_TEXTURE_2D, floorTexture);                    // bind the texture
    glNormal3f(0, 1.0f, 0);
    shapes.cuboid(gWidth / 2.0, 0.1, gDepth / 2.0);
    glPopMatrix();
    glEndList();
}