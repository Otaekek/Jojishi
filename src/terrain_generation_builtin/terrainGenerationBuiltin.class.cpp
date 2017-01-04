#include "terrainGenerationBuiltin.class.hpp"
#include <ctime>
t_biom		terrainGenerationBuiltin::bioms[4096] = {0};
uint32_t	terrainGenerationBuiltin::numBiom = 0;

void		terrainGenerationBuiltin::init()
{

}

void		terrainGenerationBuiltin::update()
{
	for (uint32_t i = 0; i < numBiom; i++)
		for (uint32_t j = 0; j < bioms[i].numFrag; j++)
			renderBuiltIn::render_me(bioms[i].renderGoHandler[j]);
}

t_material	handle_material()
{
	t_material material = {0};

	material.diffuse[0] = 1;
	return (material);
}

void	create_normal(float a, float b, float c, float d, float e, float f, float g, float h, float *outvec)
{
	glm::vec3 base = glm::vec3(0, 1, 0);

	base.x = -(c - a + 2 * ( e - d) + h - f);
	base.z = -(f - a + 2 * (g - b) + h - c);
	glm::normalize(base);
	outvec[0] = base.x;
	outvec[1] = base.y;
	outvec[2] = base.z;
}

void	create_vbo(int32_t sizex, int32_t sizey, float *data, t_renderMeshData *meshData)
{
	float		*vertex;
	uint32_t	*indices;

	vertex = (float*)malloc(sizeof(float) * sizey * sizey * 80);
	indices = (uint32_t*)malloc(sizeof(uint32_t) * sizex * sizey * 18 * 3 * 6);

	meshData->vaoId = renderDataSys::createVAO();
	meshData->vertexNum = sizex * sizey;
	meshData->indiceNum = sizex * sizey;
	meshData->material = handle_material();

	for (int32_t i = 0; i < sizex; i++)
	{
		for (int32_t j = 0; j < sizey; j++)
		{
			vertex[i * sizey * 8 + j * 8] = i;
			vertex[i * sizey * 8 + j * 8 + 1] = data[i * sizey + j];
			vertex[i * sizey * 8 + j * 8 + 2] = j;

			create_normal(data[i * sizey + j - 1 - sizex], data[i * sizey + j - sizex], data[i * sizey + j - sizex],
				data[i * sizey + j - 1], data[i * sizey + j + 1],
				data[i * sizey + j - 1 + sizex], data[i * sizey + j + sizex], data[i * sizey + j + 1 + sizex],
				&vertex[i * sizey * 8 + j * 8 + 3]);

			vertex[i * sizey * 8 + j * 8 + 6] = 0;
			vertex[i * sizey * 8 + j * 8 + 7] = 0;
		}
	}
/*
	for (uint32_t i = 0; i + 6 < sizey * sizex * 6 * 6; i += 6)
	{
		indices[i * 6 + 0] = i / 6 + sizex;
		indices[i * 6 + 1] = i / 6 + 0;
		indices[i * 6 + 2] = i / 6 + 1;

		indices[i * 6 + 3] = i / 6 + 1;
		indices[i * 6 + 4] = i / 6 + sizex + 1;
		indices[i * 6 + 5] = i / 6 + sizex;
	}
*/
	for (uint32_t i = 0; i < 240000; i += 3)
	{
		indices[i * 3 + 0] = i / 3 + sizex;
		indices[i * 3 + 1] = i / 3;
		indices[i * 3 + 2] = i / 3 + 2;
	}
	meshData->vboVerticeId = renderDataSys::createVBO_VNT(vertex, sizey * sizex, meshData->vaoId);
	meshData->indiceBufferId = renderDataSys::createVBO_Indice(indices, sizex * sizey * 12 * 30, meshData->vaoId);
	meshData->indiceNum = sizex * 9 - 9 + 18;
	free(indices);
	free(vertex);
}

void update_object(uint32_t sizex, uint32_t sizey, float *data, t_renderMeshData *meshData)
{
	meshData->has_child = false;
	meshData->child = 0;
	create_vbo(sizex, sizey, data, meshData);
}

void		fill_data(float *data, uint32_t	size)
{
	for (uint32_t i = 0; i < size * size; i++)
		data[i] = ((float)rand() / RAND_MAX) * 1;
}

void		terrainGenerationBuiltin::add_biom(float posx, float posy, uint32_t size)
{
	t_biom				biom;
	uint32_t			i;
	uint32_t			meshDataHandler;
	t_node				*node;

	biom.posy = posy;
	biom.posx = posx;
	biom.size = size;
	biom.dataRef = staticMemoryManager::create_asset(1, size * size * sizeof(float));
	fill_data((float*)staticMemoryManager::get_data_ptr(biom.dataRef), size);
	for (i = 0; i * FRAGMENT_SIZE * FRAGMENT_SIZE < size * size && FRAGMENT_SIZE < size && i == 0; i++)
	{
		meshDataHandler = staticMemoryManager::create_asset(1, sizeof(t_node));
		node = (t_node*)staticMemoryManager::get_data_ptr(meshDataHandler);
		node->has_mesh = 1;
		node->childNum = 0;
		node->meshs = staticMemoryManager::create_slot_child(staticMemoryManager::E_OBJ_FILE);
		renderDataSys::set_programm(E_DEFAULT, meshDataHandler);
		biom.renderGoHandler[i] = renderBuiltIn::create();
		(renderBuiltIn::get_renderGO(biom.renderGoHandler[i]))->assetHandler = meshDataHandler;
		(renderBuiltIn::get_renderGO(biom.renderGoHandler[i]))->transformHandler = transformBuiltin::create();
		update_object(FRAGMENT_SIZE, FRAGMENT_SIZE,
			(float*)staticMemoryManager::get_data_ptr(biom.dataRef), (t_renderMeshData*)staticMemoryManager::get_data_ptr(node->meshs));
	}
	biom.numFrag = i;
	bioms[numBiom++] = biom;
}
//(i * FRAGMENT_SIZE) % size, (i * FRAGMENT_SIZE) / size * FRAGMENT_SIZE,
