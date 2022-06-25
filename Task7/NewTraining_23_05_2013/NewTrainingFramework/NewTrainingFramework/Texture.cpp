#include "stdafx.h"
#include "Texture.h"
#include "Log.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

#define TAG "Texture"

Texture::Texture()
{
	
}

Texture::Texture(int program)
{
	this->program = program;
}

Texture::~Texture()
{
	if (textureHandle)
		glDeleteTextures(1, &textureHandle);

}

void Texture::Init(const char * file, bool tiling)
{
	// create the OpenGL ES texture resource and get the handle
	glGenTextures(1, &textureHandle);
	// bind the texture to the 2D texture type
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// create CPU buffer and load it with the image data
	int width, height, bpp; 
	
	Log::GetInstance()->printMessage(TAG, "File name loading [%s] Texture handle [%d]", file, textureHandle);
	char * bufferTGA = LoadTGA(file, &width, &height, &bpp );

	// load the image data into OpenGL ES texture resource
	if(bpp == 24)
    {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA);
	}

	// free the client memory
	delete [] bufferTGA; 

	//set the filters for minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// generate the mipmap chain
	glGenerateMipmap(GL_TEXTURE_2D);
	//set the wrapping modes
	if (tiling)
    {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
    {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
}


void Texture::Init(const char * file)
{
	//This is gonna kick ass!
}

GLuint Texture::getTexHandle()
{
	return textureHandle;
}

void Texture::setID(unsigned int id)
{
	m_ID = id;
}

unsigned int Texture::getID()
{
	return m_ID;
}

//int Texture::getUniformLocation()
//{
//	return uniformLocation;
//}