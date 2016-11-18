#ifndef fileLoader_CLASS_HPP
#define fileLoader_CLASS_HPP


#include "../renderer/meshData.hpp"
#include "../memory_allocator/stackAllocator.class.hpp"
#include "../../assimp/include/assimp/Importer.hpp"
#include "../../assimp/include/assimp/scene.h"
#include "../../assimp/include/assimp/postprocess.h"

#include "../../inc/jojishi.hpp"
#include "../renderer/renderDataSys.class.hpp"

#include "../job_system/jobSystem.hpp"
#include "../asset_database_system/assetSystem.class.hpp"
#include <map>
#include "../../inc/jojishi.hpp"
#include <string>

class fileLoader {

public:
	
	fileLoader();
	~fileLoader();

	static uint64_t get_fs_asset(std::string path);

private :
	
	static void load_file(void *data);
	static std::map<std::string, void (*)(void*)> extension_to_function;
	static const aiScene 		*assimp_load(char *path, Assimp::Importer importer);
	static void 				load_obj(void *data);
	static std::map<std::string, uint64_t> path_as_guid;
};

#endif
