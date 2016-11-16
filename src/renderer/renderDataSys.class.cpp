#include "renderDataSys.class.hpp"

renderDataSys::renderDataSys()
{

}

renderDataSys::~renderDataSys()
{

}

uint32_t renderDataSys::createVAO()
{

}

uint32_t renderDataSys::createVBO_VNT(float *vertices, uint32_t vertex_size, uint32_t vaoId)
{

}

uint32_t renderDataSys::createVBO_Indice(uint32_t *indices, uint32_t indice_size, uint32_t vaoId)
{

}

void 	renderDataSys::obj_scene_to_memory_as_mesh(stackAllocator *allocator, const aiScene *scene)
{
	t_renderMeshData 			*meshData;
	aiNode 						*node;
	aiMesh						*mesh;
	float 						*vertices;
	uint32_t					*indices;
	uint32_t					indices_size;
	uint32_t					vertex_size;
	void 						*to_free;

	meshData = (t_renderMeshData*)allocator->mem_alloc(sizeof(t_renderMeshData));
	node = scene->mRootNode;
	mesh = scene->mMeshes[node->mMeshes[0]];
	indices_size = mesh->mNumFaces;
	vertex_size = mesh->mNumVertices;

	to_free = allocator->get_offset();
	vertices = (float*)allocator->mem_alloc(vertex_size * sizeof(float) * 3);
	indices = (uint32_t*)allocator->mem_alloc(indices_size * 3 * sizeof(uint32_t));

	for (uint32_t i = 0; i < indices_size; i++)
	{
		for (uint32_t j = 0; j < 3; j++)
		{
			uint32_t indice = mesh->mFaces[i].mIndices[j];

			vertices[24 * i + 8 * j] = mesh->mVertices[indice].x;
			vertices[24 * i + 8 * j + 1] = mesh->mVertices[indice].y;
			vertices[24 * i + 8 * j + 2] = mesh->mVertices[indice].z;
	
			vertices[24 * i + 8 * j + 3] = mesh->mNormals[indice].x;
			vertices[24 * i + 8 * j + 4] = mesh->mNormals[indice].y;
			vertices[24 * i + 8 * j + 5] = mesh->mNormals[indice].z;
	
			vertices[24 * i + 8 * j + 6] = mesh->mTextureCoords[0][indice].x;
			vertices[24 * i + 8 * j + 7] = mesh->mTextureCoords[0][indice].y;
		}
	}

	meshData->vaoId = renderDataSys::createVAO();
	meshData->vboVerticeId = renderDataSys::createVBO_VNT(vertices, vertex_size, meshData->vaoId);
	meshData->vboIndiceId = renderDataSys::createVBO_Indice(indices, indices_size, meshData->vaoId);
	meshData->indiceNum = indices_size * 3;
	allocator->mem_free((char*)allocator->get_offset() - (char*)to_free);
}
