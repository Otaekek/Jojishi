#include "terrainGenerationBuiltin.class.hpp"

t_biom		terrainGenerationBuiltin::bioms[4096] = {0};
uint32_t	terrainGenerationBuiltin::numBiom = 0;

void		terrainGenerationBuiltin::init()
{

}

void		terrainGenerationBuiltin::update()
{

}

void	create_vbo(uint32_t offsetx, uint32_t offsety, uint32_t sizex, uint32_t sizey, float *data, t_renderMeshData *meshData)
{
	float		vertex[sizey * sizex * 8];
	uint32_t	indices[sizex * sizey];
	t_material	material;

	memset(&material, 0, sizeof(t_material));
	meshData->vaoId = renderDataSys::createVAO();
	meshData->vertexNum = sizex * sizey;
	meshData->indiceNum = sizex * sizey;
	meshData->material = material;
	for (uint32_t i = 0; i < sizex; i++)
	{
		for (uint32_t j = 0; j < sizey; j++)
		{
			vertex[i * j * 8] = i + offsetx;
			vertex[i * j * 8 + 1] = j + offsety;
			vertex[i * j * 8 + 2] = data[i * j];
	
			vertex[i * j * 8 + 3] = 0;
			vertex[i * j * 8 + 4] = 1;
			vertex[i * j * 8 + 5] = 0;

			vertex[i * j * 8 + 6] = 0;
			vertex[i * j * 8 + 7] = 0;
		}
	}
	for (uint32_t i = 0; i + 6 < sizey * sizex; i += 6)
	{
		indices[i] = i; 
		indices[i + 1] = i + 1; 
		indices[i + 2] = i + sizey;

		indices[i + 3] = i + 1; 
		indices[i + 1 + 3] = i + sizey + 1;
		indices[i + 2 + 3] = i + sizey; 
	}
	meshData->vboVerticeId = renderDataSys::createVBO_VNT(vertex, sizey * sizex, meshData->vaoId);
	meshData->indiceBufferId = renderDataSys::createVBO_Indice(indices, sizex * sizey, meshData->vaoId);
}

void		update_object(uint32_t offsetx, uint32_t offsety, uint32_t sizex, uint32_t sizey, float *data)
{
	t_renderMeshData *meshData;

	meshData->has_child = false;
}

void		terrainGenerationBuiltin::add_biom(float posx, float posy, float sizex, float sizey)
{
	t_biom				biom;
	uint32_t			i;
	uint32_t			size_frag_y;
	uint32_t			size_frag_x;

	biom.posy = posy;
	biom.posx = posx;
	biom.sizex = sizex;
	biom.sizey = sizey;
	biom.dataRef = staticMemoryManager::create_asset(1, sizex * sizey * sizeof(float));
	bioms[numBiom++] = biom;
	for (i = 0; i < (sizex * sizey) / FRAGMENT_SIZE; i++)
	{
		update_object( sizex, sizey);
	}
	i = (sizex * sizey) % FRAGMENT_SIZE;
	if (i > 0)
		;
	//update_object(sizex, sizey, data);
}

	// bool			has_child;

	// GLuint			textureHandler;
	// GLuint			vaoId;
	// GLuint			vertexNum;
	// GLuint			vboVerticeId;
	// GLuint			indiceNum;
	// GLuint			indiceBufferId;
	// GLuint			*indices;
	// GLuint			diffuseText;
	// GLuint			specularTexts;

	// GLuint			child;

	// float 			*vbo;
	// glm::mat4		initialTransform;
	// t_material		material;
