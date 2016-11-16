#include "genericParser.class.hpp"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

genericParser::genericParser()
{
	extension_to_function["obj"] = &genericParser::obj_scene_to_memory_as_mesh;
}

genericParser::~genericParser()
{

}

void 	genericParser::load_file(void *data)
{
	t_loadHeader 			*loadHeader;
	char 					*path;
	const aiScene			*scene;
	char 					extenstion[10] = {0};
	uint32_t				j;
	Assimp::Importer 		importer;

	loadHeader = (t_loadHeader*)data;
	path = (char *)((char*)data + sizeof(t_loadHeader));
	j = strlen(path);
   	scene = importer.ReadFile( std::string(path), 
	aiProcess_CalcTangentSpace | 
	aiProcess_Triangulate |
	aiProcess_JoinIdenticalVertices |
	aiProcess_SortByPType);

   	for (uint32_t i = 0; i > 0 && i < 10 && path[j - i] != '.'; i++)
   		extenstion[i] = path[j - i];
	for (uint32_t i = 0; i < strlen(extenstion) / 2; i++)
	{
		char c = extenstion[i];
		extenstion[i] = extenstion[strlen(extenstion) - i];
		extenstion[strlen(extenstion) - i] = c;
	}
	if (extension_to_function[extenstion] == NULL)
		return ;
	CALL_MEMBER_FN(*this, extension_to_function[extenstion])(loadHeader->allocator, scene);
}

void genericParser::obj_scene_to_memory_as_mesh(stackAllocator *allocator, const aiScene *scene)
{
	t_meshData 					*meshData;
	aiNode 						*node;
	aiMesh						*mesh;
	uint32_t					indices_size;
	uint32_t					vertex_size;

	meshData = (t_meshData*)allocator->mem_alloc(sizeof(t_meshData));
	node = scene->mRootNode;
	mesh = scene->mMeshes[node->mMeshes[0]];
	indices_size = mesh->mNumFaces;
	vertex_size = mesh->mNumVertices;
	meshData->vertex = (float*)allocator->mem_alloc(vertex_size * sizeof(float) * 3);
	meshData->uv = (float*)allocator->mem_alloc(vertex_size * sizeof(float) * 2);
	meshData->normal = (float*)allocator->mem_alloc(vertex_size * sizeof(float) * 3);
	meshData->indice = (uint32_t*)allocator->mem_alloc(indices_size * 3 * sizeof(uint32_t));
	meshData->vertex_size = vertex_size;
	meshData->indices_size = indices_size * 3;
	for (uint32_t i = 0; i < indices_size; i++)
	{
		for (uint8_t j = 0; j < 3; j++)
		{
			uint32_t indice = mesh->mFaces[i][j];
			meshData->vertex[3 * indice] = mesh->mVertices[];
		}
	}
}

