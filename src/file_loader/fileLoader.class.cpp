#include "fileLoader.class.hpp"
#include <iostream>
#include <fstream>
#include <string>

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

std::map<std::string, void (*)(void*)>  	fileLoader::extension_to_function;
std::map<std::string, uint32_t> 			fileLoader::path_as_guid;

fileLoader::fileLoader()
{

}

void fileLoader::init()
{
	extension_to_function["obj"] = &fileLoader::load_obj;
	extension_to_function["blend"] = &fileLoader::load_obj;
	extension_to_function["C4D"] = &fileLoader::load_obj;
	extension_to_function["c4d"] = &fileLoader::load_obj;
	extension_to_function["3ds"] = &fileLoader::load_obj;
	extension_to_function["3DS"] = &fileLoader::load_obj;
	extension_to_function["dae"] = &fileLoader::load_obj;
	extension_to_function["max"] = &fileLoader::load_obj;
	extension_to_function["fbx"] = &fileLoader::load_obj;
	extension_to_function["ma"] = &fileLoader::load_obj;
	extension_to_function["jpg"] = &texture_builtin::load_texture;
	extension_to_function["tga"] = &texture_builtin::load_texture;
	extension_to_function["bmp"] = &texture_builtin::load_texture;
	extension_to_function["png"] = &texture_builtin::load_texture;
	extension_to_function["jpeg"] = &texture_builtin::load_texture;
	extension_to_function["JPG"] = &texture_builtin::load_texture;
}

fileLoader::~fileLoader()
{

}

uint32_t			fileLoader::get_fs(std::string path)
{
	if (path_as_guid[path] != 0)
		return (path_as_guid[path]);
	return 0;
}

char 		*fileLoader::readfile(std::string path)
{
	std::string line;
	std::string file;
	std::ifstream myfile(path);
	if (myfile.is_open())
	{
		while ( getline (myfile, line) )
			file += line + '\n';
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
		exit(0);
	}
	printf("%s\n", file.c_str());
	return ((char*)file.c_str());
}

uint32_t fileLoader::load_fs_asset_async(std::string path, uint32_t cluster)
{
	t_job			job;
	uint32_t 		ref;
	t_loadHeader	*loadheader;

	if (path_as_guid[path] != 0)
		return (path_as_guid[path]);
	ref = staticMemoryManager::assign_asset(cluster);
	loadheader = (t_loadHeader*)job.data;
	memcpy(loadheader->path, path.c_str(), strlen(path.c_str()) + 1);
	job.fptr = load_file;
	loadheader->ref = ref;
	loadheader->cluster = cluster;
	path_as_guid[path] = ref;
	jobHandler::push_job(job);
	return (ref);
}

uint32_t fileLoader::load_fs_asset_sync(std::string path, uint32_t cluster)
{
	t_job			job;
	uint32_t 		ref;
	t_loadHeader	*loadheader;

	if (path_as_guid[path] != 0)
		return (path_as_guid[path]);
	ref = staticMemoryManager::assign_asset(cluster);
	loadheader = (t_loadHeader*)job.data;
	memcpy(loadheader->path, path.c_str(), strlen(path.c_str()) + 1);
	job.fptr = load_file;
	loadheader->ref = ref;
	loadheader->cluster = cluster;
	path_as_guid[path] = ref;
	job.fptr(job.data);
	return (ref);
}

const aiScene 	*fileLoader::assimp_load(char *path, Assimp::Importer *importer)
{
	const					aiScene *scene;

	scene = importer->ReadFile( std::string(path),
	aiProcess_CalcTangentSpace |
	aiProcess_Triangulate |
	aiProcess_JoinIdenticalVertices |
	aiProcess_SortByPType |
	aiProcess_ImproveCacheLocality |
	aiProcess_GenNormals |
	aiProcess_OptimizeMeshes |
	aiProcess_OptimizeGraph |
	aiProcess_GenUVCoords |
	aiProcess_JoinIdenticalVertices);
	return (scene);
}

void 			fileLoader::load_obj(void *data)
{
	Assimp::Importer 		importer;
	const					aiScene *scene;
	t_loadHeader 			*loadHeader;
	char 					*path;

	loadHeader = (t_loadHeader*)data;
	path = loadHeader->path;
	scene = assimp_load(path, &importer);
	if (scene == NULL)
	{
		staticMemoryManager::set_asset_state(staticMemoryManager::E_ERR, loadHeader->ref);
		printf("Error when loading %s: %s.\n", path, (importer.GetErrorString()));
		return ;
	}
	renderDataSys::obj_scene_to_memory_as_mesh(scene, path, loadHeader->ref, loadHeader->cluster);
	staticMemoryManager::set_asset_state(staticMemoryManager::E_LOADED, loadHeader->ref);
}

void 			fileLoader::load_file(void *data)
{
	t_loadHeader 			*loadHeader;
	char 					*path;
	char 					extenstion[100] = {0};
	uint32_t				j;

	loadHeader = (t_loadHeader*)data;
	path = loadHeader->path;
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
		staticMemoryManager::set_asset_state(staticMemoryManager::E_ERR, loadHeader->ref);
		printf("Error when loading %s: File type not handled.\n", path);
		return ;
	}
	extension_to_function[extenstion](data);
	staticMemoryManager::set_asset_state(staticMemoryManager::E_LOADED, loadHeader->ref);
}


