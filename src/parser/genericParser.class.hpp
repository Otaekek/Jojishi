#ifndef GENERICPARSER_CLASS_HPP
#define GENERICPARSER_CLASS_HPP


#include "../renderer/meshData.hpp"
#include "../memory_allocator/stackAllocator.class.hpp"
#include "../../assimp/include/assimp/Importer.hpp"
#include "../../assimp/include/assimp/scene.h"
#include "../../assimp/include/assimp/postprocess.h"


#include "../renderer/renderDataSys.class.hpp"

#include "../job_system/jobSystem.hpp"
#include "../asset_database_system/assetSystemWorker.class.hpp"
#include <map>
#include <string>

typedef struct 			s_parserHeader {
	stackAllocator 		*allocator;
	uint64_t 			ref;
	char 				*path;
}						t_parserHeader;

class genericParser {

public:
	
	genericParser();
	~genericParser();

	static void load_file(void *data);
	
	static void 	parse_path_and_handle_scene(std::string path);

	static std::map<std::string, void (*)(stackAllocator *, const aiScene *)> extension_to_function;
};

#endif
