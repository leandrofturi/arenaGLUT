#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

class RawLoader {
public:
	RawLoader(void);
	~RawLoader(void);

	GLuint LoadTextureRAW(const char * filename, int wrap, int width, int height);
};

