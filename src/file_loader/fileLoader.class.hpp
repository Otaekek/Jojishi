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

typedef struct 			s_loadHeader {
	uint32_t 			ref;
	uint32_t			cluster;
	char				path[1024];
}						t_loadHeader;

class fileLoader {

public:
	
	fileLoader();
	~fileLoader();

	static uint32_t 	load_fs_asset_assync(std::string path, uint32_t cluster);
	static uint32_t 	load_fs_asset_sync(std::string path, uint32_t cluster);
	static void 		init();
	static void 		load_file(void *data);
	static uint32_t		get_fs(std::string path);

	static char 		*readfile(std::string path);
private :
	
	static std::map<std::string, void (*)(void*)> 	extension_to_function;
	static const aiScene 							*assimp_load(char *path, Assimp::Importer *importer);
	static void 									load_obj(void *data);
	static std::map<std::string, uint32_t> 			path_as_guid;
};

#endif
