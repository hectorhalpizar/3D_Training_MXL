#include "stdafx.h"
#include <stdio.h>

#include "Model.h"
#include "Vertex.h"

Model::Model()
{
	maxVertices = 0;
	m_noIndices = 0;
	loadType = LOAD_TYPE_VERTICES;
}
	
Model::~Model()
{
	if(m_hVertexBuffer)
	{
		glDeleteBuffers(1,&m_hVertexBuffer);
		m_hVertexBuffer = NULL;
	}

	if(m_hIndexBuffer)
	{
		glDeleteBuffers(1,&m_hIndexBuffer);
		m_hIndexBuffer = NULL;
	}
}

void Model::InitModel(const char * filename)
{
	//Abriendo archivo del modelo
	FILE * pFile;
	errno_t err;
	//pFile = fopen(filename, "r"); //warning C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	if ((err = fopen_s(&pFile, filename, "r")) != 0)
	{
		esLogMessage("ERR001: Error open file [%s] with error [%d]\n", filename, err);
	}
	else
	{
		Vertex * bufferVertex;
		int * bufferIndices;

		if (loadType == LOAD_TYPE_VERTICES)
		{
			if(maxVertices == 0)
			{
				fscanf_s( pFile, "NrVertices: %d",&maxVertices);
				bufferVertex = new Vertex[maxVertices];
				esLogMessage("MSG001: Max Vertex is [%d]\n", maxVertices);
			}

			for (int cont = 0; cont < maxVertices; cont++)
			{
				Vector3 temp_vertices, temp_normals, temp_binormals, temp_tgt;
				Vector2 temp_uvs;
				if(fscanf_s( pFile, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
								&temp_vertices.x, &temp_vertices.y,  &temp_vertices.z,
								&temp_normals.x, &temp_normals.y, &temp_normals.z,
								&temp_binormals.x, &temp_binormals.y, &temp_binormals.z,
								&temp_tgt.x, &temp_tgt.y, &temp_tgt.z,
								&temp_uvs.x, &temp_uvs.y) != EOF)
				{
					bufferVertex[cont].pos    = (temp_vertices);
					bufferVertex[cont].normal = (temp_normals);
					bufferVertex[cont].binormal = (temp_binormals);
					bufferVertex[cont].tgt    = (temp_tgt);
					bufferVertex[cont].uvs    = (temp_uvs);
				}
			}

			//glGenBuffers(1, &m_hVertexBuffer);
			//glBindBuffer(GL_ARRAY_BUFFER, m_hVertexBuffer);
			//glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(Vertex), bufferVertex, GL_STATIC_DRAW);

			#if 1
			for (int cont = 0; cont < maxVertices; cont++)
				esLogMessage("MSG002: Checking on Positions in file [%.4f, %.4f, %.4f]\n", bufferVertex[cont].pos.x, bufferVertex[cont].pos.y, bufferVertex[cont].pos.z);
			#endif

			loadType = LOAD_TYPE_INDEXES;
		}

		if (loadType == LOAD_TYPE_INDEXES)
		{
			int cont;
			if(m_noIndices == 0)
			{
				fscanf_s( pFile, "NrIndices: %d",&m_noIndices);	
				cont = 0;
				bufferIndices = new int[m_noIndices];
			}

			for (; cont < m_noIndices;)
			{
				Vector3 temp_indices;
				if(fscanf_s( pFile, "   %*d.  %f, %f, %f",
								&temp_indices.x, &temp_indices.y,  &temp_indices.z) != EOF)
				{

					bufferIndices[cont] = (GLuint)temp_indices.x;
					cont++;
					bufferIndices[cont] = (GLuint)temp_indices.y;
					cont++;
					bufferIndices[cont] = (GLuint)temp_indices.z;
					cont++;

					//if(cont >= m_noIndices)
					//{                                
					//	cont = 0;
					//	loadType = LOAD_TYPE_END;
					//}
				}
			}
			
			#if 1
			for (int cont = 0; cont < m_noIndices; cont++)
			{
				if (cont % 3 == 0)
					esLogMessage("MSG006: Checking on Positions in file [%d, ", bufferIndices[cont]);
				else if (cont % 3 == 1)
					esLogMessage("%d, ", bufferIndices[cont]);
				else if (cont % 3 == 2)
					esLogMessage("%d]\n", bufferIndices[cont]);
			}
			#endif

			loadType = LOAD_TYPE_END;
		}

		if (loadType == LOAD_TYPE_END)
		{			
			glGenBuffers(1, &m_hVertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_hVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(Vertex), bufferVertex, GL_STATIC_DRAW);
			esLogMessage("MSG007: Vertex buffer loaded\n");

			glGenBuffers(1, &m_hIndexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_hIndexBuffer);
			glBufferData(GL_ARRAY_BUFFER, (m_noIndices)*sizeof(int), bufferIndices, GL_STATIC_DRAW);
			esLogMessage("MSG008: Index buffer loaded\n");
			
			fclose(pFile);
			esLogMessage("MSG003: File closed [%s]\n", filename);

			if(bufferVertex != NULL)	delete [] bufferVertex;		esLogMessage("MSG004: Deleting bufferVertex\n");
			if(bufferIndices != NULL)	delete [] bufferIndices;		esLogMessage("MSG005: Deleting bufferIndices\n");
		}
	}
}

int Model::getm_hIndexBuffer()
{
	return m_hIndexBuffer;
}

int Model::getm_hVertexBuffer()
{
	return m_hVertexBuffer;
}

int Model::getIndicesNum()
{
	return m_noIndices;
}
