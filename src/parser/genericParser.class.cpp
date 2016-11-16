#include "genericParser.class.hpp"

std::map<std::string, void (*)(stackAllocator *, const aiScene *)>  genericParser::extension_to_function;

genericParser::genericParser()
{
	extension_to_function["obj"] = &renderDataSys::obj_scene_to_memory_as_mesh;
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
	extension_to_function[extenstion](loadHeader->allocator, scene);
}


