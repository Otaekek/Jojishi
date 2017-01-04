#include "terrainGenerationBuiltin.class.hpp"

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

void	create_vbo(uint32_t sizex, uint32_t sizey, float *data, t_renderMeshData *meshData)
{
	float		*vertex;
	uint32_t	*indices;
	t_material	material;

	vertex = (float*)malloc(sizeof(float) * sizey * sizey * 8 * 10);
	indices = (uint32_t*)malloc(sizeof(uint32_t) * sizex * sizey * 30);
	memset(&material, 0, sizeof(t_material));
	meshData->vaoId = renderDataSys::createVAO();
	meshData->vertexNum = sizex * sizey;
	meshData->indiceNum = sizex * sizey;
	meshData->material = material;
	for (uint32_t i = 0; i < sizex; i++)
	{
		for (uint32_t j = 0; j < sizey; j++)
		{
			vertex[i * sizey * 8 + j * 8] = (i);
			vertex[i * sizey * 8 + j * 8 + 1] = 0;
			vertex[i * sizey * 8 + j * 8 + 2] = j;

			vertex[i * sizey * 8 + j * 8 + 3] = 0;
			vertex[i * sizey * 8 + j * 8 + 4] = 1;
			vertex[i * sizey * 8 + j * 8 + 5] = 0;

			vertex[i * sizey * 8 + j * 8 + 6] = 0;
			vertex[i * sizey * 8 + j * 8 + 7] = 0;
			printf("%d\n", i * sizey * 8 +  j * 8);
		}
	}
	for (uint32_t i = 0; i < sizey * sizex; i += 6)
	{
		indices[i * 6] = i;
		indices[i * 6 + 1] = i + 1;
		indices[i * 6 + 2] = i + sizex;

		indices[i * 6 + 3] = i + 1;
		indices[i * 6 + 1 + 3] = i + sizex;
		indices[i * 6 + 2 + 3] = i + sizex + 1;
	}
	meshData->vboVerticeId = renderDataSys::createVBO_VNT(vertex, sizey * sizex, meshData->vaoId);
	meshData->indiceBufferId = renderDataSys::createVBO_Indice(indices, sizex * sizey * 6, meshData->vaoId);
	meshData->indiceNum = sizey * sizex * 6;
	free(indices);
	free(vertex);
}

void update_object(uint32_t sizex, uint32_t sizey, float *data, t_renderMeshData *meshData)
{
	meshData->has_child = false;
	meshData->child = 0;
	create_vbo(sizex, sizey, data, meshData);
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
	for (i = 0; i * FRAGMENT_SIZE * FRAGMENT_SIZE < size * size && FRAGMENT_SIZE < size; i++)
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
