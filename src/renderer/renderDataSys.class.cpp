#include "renderDataSys.class.hpp"

renderDataSys::renderDataSys()
{

}

renderDataSys::~renderDataSys()
{

}

uint32_t renderDataSys::createVAO()
{
	return 1;
}

uint32_t renderDataSys::createVBO_VNT(float *vertices, uint32_t vertex_size, uint32_t vaoId)
{
	vertices = (float*)vertices;
	vertex_size = (uint32_t)vertex_size;
	vaoId = (uint32_t)vaoId;
	return 1;
}

uint32_t renderDataSys::createVBO_Indice(uint32_t *indices, uint32_t indice_size, uint32_t vaoId)
{
	indices = (uint32_t*)indices;
	indice_size = (uint32_t)indice_size;
	vaoId = (uint32_t)vaoId;
	return 1;
}

void 	renderDataSys::obj_scene_to_memory_as_mesh(stackAllocator *allocator, const aiScene *scene)
{
	t_renderMeshData 			*meshData;
	aiMesh						*mesh;
	float 						*vertices;
	uint32_t					*indices;
	uint32_t					indices_size;
	uint32_t					vertex_size;
	void 						*to_free;


	meshData = (t_renderMeshData*)allocator->mem_alloc(sizeof(t_renderMeshData));
	
	mesh = scene->mMeshes[0];
	indices_size = mesh->mNumFaces;
	vertex_size = mesh->mNumVertices;

	to_free = allocator->get_offset();
	vertices = (float*)allocator->mem_alloc(vertex_size * sizeof(float) * 8);
	indices = (uint32_t*)allocator->mem_alloc(indices_size * 3 * sizeof(uint32_t));

	aiFace a = mesh->mFaces[0];
	for (uint32_t i = 0; i < vertex_size; i++)
	{
		vertices[i * 8] = mesh->mVertices[i].x;
		vertices[i * 8 + 1] = mesh->mVertices[i].y;
		vertices[i * 8 + 2] = mesh->mVertices[i].z;

		vertices[i * 8 + 3] = mesh->mNormals[i].x;
		vertices[i * 8 + 4] = mesh->mNormals[i].y;
		vertices[i * 8 + 5] = mesh->mNormals[i].z;

		vertices[i * 8 + 6] = mesh->mTextureCoords[0][i].x;
		vertices[i * 8 + 7] = mesh->mTextureCoords[0][i].y;
	}
	for (uint32_t i = 0; i < indices_size; i++)
	{
		for (uint32_t j = 0; j < 3; j++)
		{
			uint32_t indice = mesh->mFaces[i].mIndices[j];
			indices[i * 3 + j] = indice;
		}
	}
	meshData->vaoId = renderDataSys::createVAO();
	meshData->vboVerticeId = renderDataSys::createVBO_VNT(vertices, vertex_size, meshData->vaoId);
	meshData->vboIndiceId = renderDataSys::createVBO_Indice(indices, indices_size, meshData->vaoId);
	meshData->indiceNum = indices_size * 3;
	allocator->mem_free((char*)allocator->get_offset() - (char*)to_free);
}
