#ifndef __MODEL__
#define __MODEL__

#include "Vertex.h"
enum LoadType
{
	LOAD_TYPE_VERTICES = 0,
	LOAD_TYPE_INDEXES,
	LOAD_TYPE_END,
} ;

class Model
{
private:
	int maxVertices;	
	int m_noIndices;
	unsigned int m_ID;                // You don’t use for the moment this data member, but when you will write the engine, here it will be kept the ID of the model from Resource Manager file.

	GLuint m_hVertexBuffer, m_hIndexBuffer;
	
	LoadType loadType;

public:
	Model();	// you need to keep always constructors very simple (only code like  variable = 0, pointer = NULL).  
				// That’s because on some platforms you can’t access the call stack before main(), so, if you have global objects (constructor will be called before main()), it’s a nightmare to identify which of those global objects has problems
	
	~Model();	//Don’t forget to put on NULL the pointers after “delete pointer”

	void InitModel(const char * filename); // You read .nfg file using fscanf_s(). You can “jump” over some values which are not relevant for you
	
	int getm_hIndexBuffer(); 
	int getm_hVertexBuffer();
	int getIndicesNum();
	
};

#endif
