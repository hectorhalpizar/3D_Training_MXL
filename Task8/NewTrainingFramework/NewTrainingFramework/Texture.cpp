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

void Texture::InitCubeTexture(const char * file)
{
	// create the OpenGL ES texture resource and get the handle
	glGenTextures(1, &textureHandle);
	// bind the texture to the 2D texture type
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureHandle);

	// create CPU buffer and load it with the image data
	int width, height, bpp; 

	Log::GetInstance()->printMessage(TAG, "File name loading [%s] Texture handle [%d]", file, textureHandle);
	char * bufferTGA = NULL;
	bufferTGA = LoadTGA(file, &width, &height, &bpp );

	int w = width / 4;
	int h = height / 3;

	char *p[6];

	for (int i = 0; i < 6; i++)	p[i] = new char[w * w * bpp / 8];
	
	p[0]=ExtractFace(bufferTGA, p[0], width, bpp, 2 * w, w);
	p[1]=ExtractFace(bufferTGA, p[1], width, bpp, 0, w);
	p[2]=ExtractFace(bufferTGA, p[2], width, bpp, w, 0);
	p[3]=ExtractFace(bufferTGA, p[3], width, bpp, w, 2 * w);
	p[4]=ExtractFace(bufferTGA, p[4], width, bpp, w, w);
	p[5]=ExtractFace(bufferTGA, p[5], width, bpp, 3 * w, w);

	// free the client memory
	delete [] bufferTGA;
	bufferTGA = NULL;

	for (int i = 0; i < 6; i++)
	{
		if (bpp == 24)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, w, h, 0, GL_RGB,GL_UNSIGNED_BYTE, p[i]);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA, w, h, 0, GL_RGBA,GL_UNSIGNED_BYTE, p[i]);
		}

		delete p[i];
		p[i] = NULL;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	//set the filters for minification and magnification
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// generate the mipmap chain
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

}

char * Texture::ExtractFace(char * bufferTGA, char * temp, int width, int bpp, int offsetX, int offsetY)
{
	int w = width/4;
    int startRead = offsetY * width * bpp/8 + offsetX * bpp/8;

    for (int i = 0; i < w; i++)
    {
        memcpy_s(temp + i * w * bpp/8, w*w*bpp/8,bufferTGA + startRead,w * bpp/8);
        startRead += width * bpp/8;
    }

    return temp;
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