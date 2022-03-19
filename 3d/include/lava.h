#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

class Lava {
private:
	GLuint lavaTexture;
	GLuint displayList;
	GLfloat width;
	GLfloat height;
	GLfloat depth;
public:
	Lava(void);
	~Lava(void);

	void init(double w, double h, double d);
	void draw();
	GLfloat getHeight(void);
	void increaseHeight();
	void decreaseHeight();
};

