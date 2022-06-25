#ifndef __TEXTURE__
#define __TEXTURE__
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Texture
{
private:
	GLuint textureHandle;
	//int uniformLocation;
	int program;

public:
	Texture(int program);
	~Texture();
	void Init(const char * file, bool tiling);
	GLuint getTexHandle();
	int getUniformLocation();
};
#endif
