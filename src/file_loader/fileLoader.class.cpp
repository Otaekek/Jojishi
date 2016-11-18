#include "fileLoader.class.hpp"

extern assetSystem g_asset_db;
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

std::map<std::string, void (*)(void*)>  	fileLoader::extension_to_function;
std::map<std::string, uint64_t> 			fileLoader::path_as_guid;

fileLoader::fileLoader()
{
	
}

void fileLoader::init()
{
	extension_to_function["obj"] = &fileLoader::load_obj;
	extension_to_function["blend"] = &fileLoader::load_obj;
}

fileLoader::~fileLoader()
{

}

uint64_t fileLoader::get_fs_asset(std::string path, assetSystemWorker::E_ASSET_TYPE type)
{
	t_job			job;
	char 			*job_path;
	uint64_t ref;

	if (path_as_guid[path] != 0)
		return (path_as_guid[path]);
	job_path = job.data + sizeof(t_loadHeader);
	memcpy(job_path, path.c_str(), strlen(path.c_str()));
	job.fptr = load_file;
	ref = (g_asset_db.load_asset(job, type));
	path_as_guid[path] = ref;
	return (ref);
}

const aiScene 	*fileLoader::assimp_load(char *path, Assimp::Importer *importer)
{	
	const					aiScene *scene;

  	scene = importer->ReadFile( std::string(path), 
	0);
	return (scene);
}

void 			fileLoader::load_obj(void *data)
{
	Assimp::Importer 		importer;
	const					aiScene *scene;
	t_loadHeader 			*loadHeader;
	char 					*path;

	loadHeader = (t_loadHeader*)data;
	path = (char *)((char*)data + sizeof(t_loadHeader));
	scene = assimp_load(path, &importer);
	if (scene == NULL)
	{
		g_asset_db.set_asset_state(assetSystem::E_ERR, loadHeader->ref);
		return ;
	}
	renderDataSys::obj_scene_to_memory_as_mesh(loadHeader->allocator, scene);
	g_asset_db.set_asset_state(assetSystem::E_LOADED, loadHeader->ref);
}

void 			fileLoader::load_file(void *data)
{
	t_loadHeader 			*loadHeader;
	char 					*path;
	char 					extenstion[10] = {0};
	uint32_t				j;

	loadHeader = (t_loadHeader*)data;
	path = (char *)((char*)data + sizeof(t_loadHeader));
	j = strlen(path);
   	for (uint32_t i = 0; (j - i) > 0 && path[j - i - 1] != '.'; i++)
   		extenstion[i] = path[j - i - 1];
	for (uint32_t i = 0; i < strlen(extenstion) / 2; i++)
	{
		char c = extenstion[i];
		extenstion[i] = extenstion[strlen(extenstion) - i - 1];
		extenstion[strlen(extenstion) - i - 1] = c;
	}
	if (extension_to_function[extenstion] == NULL)
	{
		g_asset_db.set_asset_state(assetSystem::E_ERR, loadHeader->ref);
		return ;
	}
	extension_to_function[extenstion](data);
}


