#include "genericParser.class.hpp"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

std::map<std::string, void (*)(void*)>  genericParser::extension_to_function;

genericParser::genericParser()
{
	extension_to_function["obj"] = &genericParser::load_obj;
}

genericParser::~genericParser()
{

}

const aiScene 	*genericParser::assimp_load(char *path, Assimp::Importer importer)
{	
	const					aiScene *scene;

  	scene = importer.ReadFile( std::string(path), 
	aiProcess_CalcTangentSpace | 
	aiProcess_Triangulate |
	aiProcess_JoinIdenticalVertices |
	aiProcess_SortByPType);
	return (scene);
}

void 			genericParser::load_obj(void *data)
{
	Assimp::Importer 		importer;
	const					aiScene *scene;
	t_loadHeader 			*loadHeader;
	char 					*path;

	loadHeader = (t_loadHeader*)data;
	path = (char *)((char*)data + sizeof(t_loadHeader));
	scene = assimp_load(path, importer);
	if (scene == NULL)
	{
		g_graphic_asset_db.set_asset_state(assetSystem::E_ERR, loadHeader->ref);
		return ;
	}
	renderDataSys::obj_scene_to_memory_as_mesh(loadHeader->allocator, scene);
}

void 			genericParser::load_file(void *data)
{
	t_loadHeader 			*loadHeader;
	char 					*path;
	char 					extenstion[10] = {0};
	uint32_t				j;

	loadHeader = (t_loadHeader*)data;
	path = (char *)((char*)data + sizeof(t_loadHeader));
	j = strlen(path);
   	for (uint32_t i = 0; i > 0 && i < 10 && path[j - i] != '.'; i++)
   		extenstion[i] = path[j - i];
	for (uint32_t i = 0; i < strlen(extenstion) / 2; i++)
	{
		char c = extenstion[i];
		extenstion[i] = extenstion[strlen(extenstion) - i];
		extenstion[strlen(extenstion) - i] = c;
	}
	if (extension_to_function[extenstion] == NULL)
	{
		g_graphic_asset_db.set_asset_state(assetSystem::E_ERR, loadHeader->ref);
		return ;
	}
	extension_to_function[extenstion](data);
}


