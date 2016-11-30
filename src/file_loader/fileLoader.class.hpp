#ifndef fileLoader_CLASS_HPP
#define fileLoader_CLASS_HPP


#include "../renderer/meshData.hpp"
#include "../memory_allocator/stackAllocator.class.hpp"
#include "../../assimp/include/assimp/Importer.hpp"
#include "../../assimp/include/assimp/scene.h"
#include "../../assimp/include/assimp/postprocess.h"
#include "../job_system/jobHandler.class.hpp"

#include "../../inc/jojishi.hpp"
#include "../renderer/renderDataSys.class.hpp"

#include "../job_system/jobSystem.hpp"
#include "../static_memory_manager/staticMemoryManager.class.hpp"
#include <map>
#include "../../inc/jojishi.hpp"
#include <string>
#include <iostream>
#include <fstream>

class fileLoader {

public:
	
	fileLoader();
	~fileLoader();

	static uint64_t get_fs_asset_assync(std::string path);
	static uint64_t get_fs_asset_sync(std::string path);
	static void init();
	static void load_file(void *data);

	static char 									*readfile(std::string path);
private :
	
	static std::map<std::string, void (*)(void*)> 	extension_to_function;
	static const aiScene 							*assimp_load(char *path, Assimp::Importer *importer);
	static void 									load_obj(void *data);
	static std::map<std::string, uint64_t> 			path_as_guid;
};

#endif
