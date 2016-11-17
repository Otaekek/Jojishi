#ifndef GENERICPARSER_CLASS_HPP
#define GENERICPARSER_CLASS_HPP


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
#include <string>

class genericParser {

public:
	
	genericParser();
	~genericParser();

	static void load_file(void *data);

private :

	static std::map<std::string, void (*)(void*)> extension_to_function;
	static const aiScene 		*assimp_load(char *path, Assimp::Importer importer);
	static void 				load_obj(void *data);
};

#endif
