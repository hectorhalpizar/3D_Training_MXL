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
	unsigned int m_ID;
	
public:
	Texture();
	Texture(int program);
	~Texture();
	void Init(const char * file, bool tiling);
	void Init(const char * file);
	GLuint getTexHandle();
	int getUniformLocation();
	void setID(unsigned int id);
	unsigned int getID();
	char * getFileName();
};
#endif
